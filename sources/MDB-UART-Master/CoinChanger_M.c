/*
 * CoinChanger_M.c
 *
 * Created: 18.05.2019 09:58:48
 *  Author: root
 */ 
#include "config.h"
#include "utils.h"
#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include "MDB_M.h"
#include "USART_M.h"
#include "CoinChanger_M.h"
#include "LEDControl_M.h"
#include "Settings_M.h"
#include "utils.h"
#include "myflash.h"

cciddata CoinChangerIDData;
ccsetupdata CoinChangerSetupData;
mdbdevice CoinChangerDevice;

uint8_t CoinChangerInManualFillOrPaymentMode = 0;

void GetCoinChangerSetupData()
{
	uint8_t cmd[2] = {0x09, 0x09};
	MDB_Send(cmd, 2);
	while (!MDBReceiveComplete)
	{
		MDB_read();
	}
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		if (MDB_BUFFER_COUNT > 0)
		{
			MDB_ACK();
			CoinChangerDevice.OfflinePollsCount = 5;
			CoinChangerSetupData.CoinChangerFeatureLevel = MDB_BUFFER[0];
			uint8_t cocd[2] = {MDB_BUFFER[1], MDB_BUFFER[2]};

			CoinChangerSetupData.CountryOrCurrencyCode = BCDByteToInt(cocd, sizeof(cocd));
			CoinChangerSetupData.CoinScalingFactor = MDB_BUFFER[3];
			CoinChangerSetupData.DecimalPlaces = MDB_BUFFER[4];
			uint16_t tmpcr  = MDB_BUFFER[5];
			tmpcr = (tmpcr << 8) | MDB_BUFFER[6];
			for (int i = 0; i < 16; i++)
			{
				CoinChangerSetupData.CoinsRouteable[i] = ((tmpcr & (1 << i)) != 0);
			}
			for (int i = 7; i < MDB_BUFFER_COUNT; i++)
			{
				CoinChangerSetupData.CoinTypeCredit[i - 7] = MDB_BUFFER[i];
			}
			char tmpstr[80];
			uint8_t mcvbuff[5 + CoinChangerSetupData.DecimalPlaces];
			double mindispvalue = CoinChangerSetupData.CoinScalingFactor / pow(10, CoinChangerSetupData.DecimalPlaces);
			dtostrf(mindispvalue,0,CoinChangerSetupData.DecimalPlaces,(char*)mcvbuff);
			sprintf(tmpstr,"CC*CFG*%d*%d*%s\r\n", CoinChangerSetupData.CoinChangerFeatureLevel, CoinChangerSetupData.CountryOrCurrencyCode, mcvbuff);
			EXT_UART_Transmit_S(tmpstr);
			for (int i = 0; i < 16; i++)
			{
				if (CoinChangerSetupData.CoinsRouteable[i] == 1)
				{
					uint8_t cvbuff[10 + CoinChangerSetupData.DecimalPlaces];
					uint8_t buff[18 + sizeof(cvbuff)];
					double coinvalue = (CoinChangerSetupData.CoinScalingFactor * CoinChangerSetupData.CoinTypeCredit[i]) / pow(10, CoinChangerSetupData.DecimalPlaces);
					dtostrf(coinvalue,0,CoinChangerSetupData.DecimalPlaces,(char*)cvbuff);
					XXXX_sprintf_FSTR((char*)buff,"CC*COINSUP*%d*%s*%d*%d\r\n",i + 1,cvbuff,(CoinChangerOptions.EnableAcceptCoinsBits >> i) & 0x01,(CoinChangerOptions.EnableDispenseCoinsBits >> i) & 0x01);
					EXT_UART_Transmit(buff);
				}
			}
		} else
		{
			if (MDB_BUFFER[0] == 0x00)
			{

			}
		}
	} else
	{
		EXT_UART_Transmit_S("CC*CFGERR");
		EXT_CRLF();
		if (CoinChangerDevice.OfflinePollsCount > 0) CoinChangerDevice.OfflinePollsCount--;
	}
}

// CC*COINSUP*1*0.10*1*1
// CC*COINSUP*2*0.20*1*1
// CC*COINSUP*3*0.50*1*1
// CC*COINSUP*4*1.00*1*1
//            ^ tube 
//              ^ coin value
//                   ^ - Indicates the greatest number of coins that the changer
//                     ^ - full status 1-full


void GetCoinChangerTubeStatus()
{
	uint8_t cmd[2] = {0x0a, 0x0a}; // TUBE STATUS
	MDB_Send(cmd, 2);
	while (!MDBReceiveComplete){
		MDB_read();
	}
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		if (MDB_BUFFER_COUNT > 0){
			MDB_ACK();
			CoinChangerDevice.OfflinePollsCount = 5;

			uint16_t fullflags = (MDB_BUFFER[0] << 8) | MDB_BUFFER[1];

			for (int i = 2; i < MDB_BUFFER_COUNT; i++)
			{
				if ((MDB_BUFFER[i] != 0) || ((fullflags & (1 << (i - 2))) == 1) || 1)

				{
					uint8_t tmpstr[32];
					uint8_t buff[5 + CoinChangerSetupData.DecimalPlaces];
					double coinvalue = (CoinChangerSetupData.CoinScalingFactor * CoinChangerSetupData.CoinTypeCredit[i - 2]) / pow(10, CoinChangerSetupData.DecimalPlaces);
					dtostrf(coinvalue,0,CoinChangerSetupData.DecimalPlaces,(char*)buff);
					XXXX_sprintf_FSTR((char*)tmpstr,"CC*TUBE*%d*%s*%d*%d", i - 1, buff, MDB_BUFFER[i], (fullflags & (1 << (i - 2))));
					if ((MDB_BUFFER[i] == 0x00) && ((fullflags & (1 << (i - 2))) == 1)) EXT_UART_Transmit_S("*ERR");
					EXT_UART_Transmit_S((char*)tmpstr);
					EXT_CRLF();
				}
			}
			} else{
			if (MDB_BUFFER[0] == 0x00){

			}
			}
			EXT_UART_Transmit_S("CC*TUBESTATREQ*OK");
			EXT_CRLF();
		} else {
		EXT_UART_Transmit_S("CC*TUBESTATREQ*FAIL");
		EXT_CRLF();
		if (CoinChangerDevice.OfflinePollsCount > 0) CoinChangerDevice.OfflinePollsCount--;
	}
}

void CoinChangerPollResponse()
{
	CoinChangerDevice.OfflinePollsCount = 5;
	uint8_t tmpstr[64];
	//uint8_t cvbuff[8];
	uint16_t tmplen = MDB_BUFFER_COUNT;
	uint8_t TMP[tmplen];
	memcpy(TMP, MDB_BUFFER, MDB_BUFFER_COUNT);
	for (int i = 0; i < tmplen; i++)
	{
		if ((TMP[i] >> 5) == 1)
		{
			uint16_t slugs = (TMP[i] & 0x1f);
			XXXX_sprintf_FSTR((char*)tmpstr,"CC*SLUG*%d", slugs);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
		}
		if ((TMP[i] >> 4) == 0)
		{
			char statusbuff[20];
			switch (TMP[i] & 0x0f)
			{
				case 1:
				sprintf(statusbuff,"%s","ESCROWREQ");
				break;
				case 2: // 00000010)
				sprintf(statusbuff,"%s","PAYOUTBUSY");
				break;
				case 3: // (00000011)
				sprintf(statusbuff,"%s","NOCREDIT");
				break;
				case 4: // (00000100)
				sprintf(statusbuff,"%s","BADTUBESENSOR");
				break;
				case 5:
				sprintf(statusbuff,"%s","DOUBLECOIN");
				break;
				case 6: // (00000110)
				sprintf(statusbuff,"%s","UNPLUGGED");
				break;
				case 7:
				sprintf(statusbuff,"%s","TUBEJAM");
				break;
				case 8:
				sprintf(statusbuff,"%s","ROMERROR");
				break;
				case 9:
				sprintf(statusbuff,"%s","ROUTERROR");
				break;
				case 10: // (00001010)
				sprintf(statusbuff,"%s","BUSY");
				break;
				case 11: // (00001011)
				sprintf(statusbuff,"%s","JUSTRESET");
				//The following initialization sequence is recommended for all new VMCs
				//designed after July, 2000. It should be used after �power up�, after issuing
				//the RESET command, after issuing the Bus Reset (pulling the transmit line
				//�active� for a minimum of 100 mS), or anytime a POLL command results in a
				//�JUST RESET� response (i.e., peripheral self resets).
				CoinChangerDevice.Status = 1;
				CoinChangerDevice.OfflinePollsCount = 5;
				XXXX_sprintf_FSTR((char*)tmpstr,"CC*STATUS*%s\r\n", statusbuff);
				EXT_UART_Transmit_S((char*)tmpstr);
				GetCoinChangerSetupData();
				if (CoinChangerSetupData.CoinChangerFeatureLevel >= 2)
				{
					GetCoinChangerIdentification();
					CoinChangerEnableFeatures();
					GetCoinChangerDiagnosticStatus();
				}
				CoinChangerControlledManualFillReport();
				GetCoinChangerTubeStatus();
				return;
				case 12: // (00001100)
				sprintf(statusbuff,"%s","COINJAM");
				break;
				case 13: // (00001101)
				sprintf(statusbuff,"%s","FISHING");
				break;
			}
			XXXX_sprintf_FSTR((char*)tmpstr,"CC*STATUS*%s", statusbuff);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
		}
		if ((TMP[i] >> 7) == 1) // Coins Dispensed Manually
		{
			uint8_t cdmnumber = ((TMP[i] & 0x70) >> 4);
			uint8_t coinsintube = (TMP[i + 1]);
			uint8_t cointype = TMP[i] & 0x0f;
			uint8_t cvbuff[5 + CoinChangerSetupData.DecimalPlaces];
			double coinvalue = (CoinChangerSetupData.CoinScalingFactor * CoinChangerSetupData.CoinTypeCredit[cointype]) / pow(10, CoinChangerSetupData.DecimalPlaces);
			dtostrf(coinvalue,0,CoinChangerSetupData.DecimalPlaces,(char*)cvbuff);
			XXXX_sprintf_FSTR((char*)tmpstr,"CC*MANUALDISP*%d*%s*%d*%d", cointype + 1, cvbuff, cdmnumber, coinsintube);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
			i++;
		} else if ((TMP[i] >> 6) == 1) // Coins Deposited
		{
			uint8_t coinrouting = ((TMP[i] & 0x30) >> 4);
			uint8_t coinsintube = (TMP[i + 1]);
			uint8_t cointype = TMP[i] & 0x0f;
			uint8_t cvbuff[5 + CoinChangerSetupData.DecimalPlaces];
			double coinvalue = (CoinChangerSetupData.CoinScalingFactor * CoinChangerSetupData.CoinTypeCredit[cointype]) / pow(10, CoinChangerSetupData.DecimalPlaces);
			dtostrf(coinvalue,0,CoinChangerSetupData.DecimalPlaces,(char*)cvbuff);
			char routbuff[10];
			switch (coinrouting)
			{
				case 0:
				sprintf(routbuff,"%s", "CASHBOX");
				break;
				case 1:
				sprintf(routbuff,"%s", "TUBE");
				break;
				case 2:
				sprintf(routbuff,"%s", "NA");
				break;
				case 3:
				sprintf(routbuff,"%s", "REJECT");
				break;
			}
			XXXX_sprintf_FSTR((char*)tmpstr,"CC*DEPOSIT*%d*%s*%s*%d", cointype + 1, cvbuff, routbuff, coinsintube);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
			i++;
		}
	}
}

void CoinChangerEnableCoinType(uint8_t CoinType, uint8_t EnableAccept, uint8_t EnableDispense)
{
	uint8_t buff[27 + CoinChangerSetupData.DecimalPlaces];
	CoinChangerOptions.EnableAcceptCoinsBits = (EnableAccept == 1) ? (CoinChangerOptions.EnableAcceptCoinsBits | (1 << (CoinType - 1))) : (CoinChangerOptions.EnableAcceptCoinsBits & ~(1 << (CoinType - 1)));
	CoinChangerOptions.EnableDispenseCoinsBits = (EnableDispense == 1) ? (CoinChangerOptions.EnableDispenseCoinsBits | (1 << (CoinType - 1))) : (CoinChangerOptions.EnableDispenseCoinsBits & ~(1 << (CoinType - 1)));
	WriteCoinChangerOptions();
	uint8_t cvbuff[5 + CoinChangerSetupData.DecimalPlaces];
	double coinvalue = (CoinChangerSetupData.CoinScalingFactor * CoinChangerSetupData.CoinTypeCredit[CoinType - 1]) / pow(10, CoinChangerSetupData.DecimalPlaces);
	dtostrf(coinvalue,0,CoinChangerSetupData.DecimalPlaces,(char*)cvbuff);
	XXXX_sprintf_FSTR((char*)buff,"CC*COINCFG*%d*%s*%d*%d*", CoinType, cvbuff, (EnableAccept == 1), (EnableDispense == 1));
	EXT_UART_Transmit(buff);
	EXT_UART_OK();
}




void EXT_UART_PrintHex(const uint8_t *data, uint16_t len) //amilek:temporary function
{
	char buf[5]; // "FF " + null
	for (uint16_t i = 0; i < len; i++)
	{
		snprintf(buf, sizeof(buf), "%02X ", data[i]);
		EXT_UART_Transmit((uint8_t*)buf);  
	}
	EXT_UART_Transmit((uint8_t*)"\r\n");
}

void CoinChangerEnableAcceptCoins(uint16_t EnableAcceptCoinsBitsMask, uint16_t EnableDispenseCoinsBitsMask)
{
	uint8_t cmd[6];
	uint16_t EnableAcceptCoinsBits = CoinChangerOptions.EnableAcceptCoinsBits & EnableAcceptCoinsBitsMask;
	uint16_t EnableDispenseCoinsBits = CoinChangerOptions.EnableDispenseCoinsBits & EnableDispenseCoinsBitsMask;
	cmd[0] = 0x0c; // COIN TYPE 0CH
	cmd[1] = (EnableAcceptCoinsBits >> 8) & 0xff;
	cmd[2] = (EnableAcceptCoinsBits >> 0) & 0xff;
	cmd[3] = (EnableDispenseCoinsBits >> 8) & 0xff;
	cmd[4] = (EnableDispenseCoinsBits >> 0) & 0xff;
	cmd[5] = ((cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4]) & 0xff);
	MDB_Send(cmd, 6);
	while (!MDBReceiveComplete){
		MDB_read();
	}
	EXT_UART_Transmit_S("CC*ENABLE*");
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		if (MDB_RESPONSE_TYPE == MDB_RESP_ACK)
		{
			EXT_UART_OK();
			CoinChangerDevice.OfflinePollsCount = 5;
			return;
		}
	}
	EXT_UART_FAIL();
	if (CoinChangerDevice.OfflinePollsCount > 0) CoinChangerDevice.OfflinePollsCount--;
}

void CoinChangerDisableAcceptCoins()
{
	uint8_t cmd[6];
	cmd[0] = 0x0c;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;
	cmd[5] = ((cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4]) & 0xff);
	MDB_Send(cmd, 6);
	while (!MDBReceiveComplete){
		MDB_read();
	}
	EXT_UART_Transmit_S("CC*DISABLE*");
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		if (MDB_RESPONSE_TYPE == MDB_RESP_ACK)
		{
			EXT_UART_OK();
			CoinChangerDevice.OfflinePollsCount = 5;
			return;
		}
	}
	EXT_UART_FAIL();
	if (CoinChangerDevice.OfflinePollsCount > 0) CoinChangerDevice.OfflinePollsCount--;
}

void CoinChangerDispense(uint8_t DispenseParams)
{
	uint8_t cmd[3];
	cmd[0] = 0x0d;
	cmd[1] = DispenseParams;
	cmd[2] = ((cmd[0] + cmd[1]) & 0xff);
	MDB_Send(cmd, 3);
	while (!MDBReceiveComplete){
		MDB_read();
	}
	EXT_UART_Transmit_S("CC*DISPENSE*");
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		if (MDB_RESPONSE_TYPE == MDB_RESP_ACK)
		{
			CoinChangerDevice.Status = 2;//awaiting dispense
			EXT_UART_OK();
			CoinChangerDevice.OfflinePollsCount = 5;
			return;
		}
		else if (MDB_RESPONSE_TYPE == MDB_RESP_NAK)
		{
			EXT_UART_NAK();
		}
		else if (MDB_RESPONSE_TYPE == MDB_RESP_DATA)
		{
			EXT_UART_UNK_DATA();
		}
		else
		{
			EXT_UART_UNK();
		}
	} else {
		EXT_UART_FAIL();
	}
	if (CoinChangerDevice.OfflinePollsCount > 0) CoinChangerDevice.OfflinePollsCount--;
}

void CoinChangerAlternativePayout(uint8_t PayoutValue)
{
	uint8_t cmd[4];
	cmd[0] = 0x0f;
	cmd[1] = 0x02;
	cmd[2] = PayoutValue;
	cmd[3] = ((cmd[0] + cmd[1] + cmd[2]) & 0xff);
	MDB_Send(cmd, 4);
	while (!MDBReceiveComplete){
		MDB_read();
	}
	EXT_UART_Transmit_S("CC*SUMPAYOUT*");
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		CoinChangerDevice.OfflinePollsCount = 5;
		if (MDB_RESPONSE_TYPE == MDB_RESP_ACK)
		{
			CoinChangerDevice.Status = 3;//Awaiting dispense complete
			EXT_UART_OK();
			return;
		}
	}
	EXT_UART_FAIL();
	if (CoinChangerDevice.OfflinePollsCount > 0) CoinChangerDevice.OfflinePollsCount--;
}

void CoinChangerAlternativePayoutStatus()
{
	uint8_t cmd[3];
	cmd[0] = 0x0f;
	cmd[1] = 0x03;
	cmd[2] = 0x12;
	MDB_Send(cmd, 3);
	while (!MDBReceiveComplete){
		MDB_read();
	}
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		if (MDB_RESPONSE_TYPE == MDB_RESP_DATA)
		{
			MDB_ACK();
			CoinChangerDevice.OfflinePollsCount = 5;
			for (int i = 0; i < MDB_BUFFER_COUNT; i++)
			{
				if (MDB_BUFFER[i] > 0)
				{
					uint8_t tmpstr[10 + CoinChangerSetupData.DecimalPlaces];
					EXT_UART_Transmit_S("CC*PAYSTATUS");
					uint8_t cvbuff[5 + CoinChangerSetupData.DecimalPlaces];
					double coinvalue = (CoinChangerSetupData.CoinScalingFactor * CoinChangerSetupData.CoinTypeCredit[i]) / pow(10, CoinChangerSetupData.DecimalPlaces);
					dtostrf(coinvalue,0,CoinChangerSetupData.DecimalPlaces,(char*)cvbuff);
					sprintf((char*)tmpstr,"*%s", cvbuff);
					EXT_UART_Transmit_S((char*)tmpstr);
					sprintf((char*)cvbuff,"*%d", MDB_BUFFER[i]);
					EXT_UART_Transmit(cvbuff);
					EXT_CRLF();
				}
			}
			GetCoinChangerTubeStatus();
		} else
		{
			EXT_UART_Transmit_S("CC*PAYSTATUS*BUSY");
			EXT_CRLF();
		}
	} else
	{
		EXT_UART_Transmit_S("CC*PAYSTATUS*FAIL");
		EXT_CRLF();
		if (CoinChangerDevice.OfflinePollsCount > 0) CoinChangerDevice.OfflinePollsCount--;
	}
}

void CoinChangerAlternativePayoutValue()
{
	uint8_t cmd[3];
	cmd[0] = 0x0f;
	cmd[1] = 0x04;
	cmd[2] = 0x13;
	MDB_Send(cmd, 3);
	while (!MDBReceiveComplete){
		MDB_read();
	}
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		if (MDB_RESPONSE_TYPE == MDB_RESP_DATA)
		{
			MDB_ACK();
			CoinChangerDevice.OfflinePollsCount = 5;
			uint8_t cvbuff[5 + CoinChangerSetupData.DecimalPlaces];
			double coinvalue = (CoinChangerSetupData.CoinScalingFactor * MDB_BUFFER[0]) / pow(10, CoinChangerSetupData.DecimalPlaces);
			dtostrf(coinvalue,0,CoinChangerSetupData.DecimalPlaces,(char*)cvbuff);
			EXT_UART_Transmit_S("CC*PAID*");
			EXT_UART_Transmit(cvbuff);
			EXT_CRLF();
		} else
		{
			EXT_UART_Transmit_S("CC*PAYOUTEND");
			EXT_CRLF();
			CoinChangerDevice.Status = 1;
			CoinChangerAlternativePayoutStatus();
		}
	} else
	{
		EXT_UART_Transmit_S("CC*PAYSTATUSFAIL");
		EXT_CRLF();
		if (CoinChangerDevice.OfflinePollsCount > 0) CoinChangerDevice.OfflinePollsCount--;
	}
}

void CoinChangerConfigFeatures(uint8_t AlternativePayout, uint8_t ExtendedDiagnostic, uint8_t ControlledManualFillAndPayout)
{
	CoinChangerOptions.EnableExtOptionsBits = (AlternativePayout == 1) ? (CoinChangerOptions.EnableExtOptionsBits | 1) : (CoinChangerOptions.EnableExtOptionsBits & 0xfe);
	CoinChangerOptions.EnableExtOptionsBits = (ExtendedDiagnostic == 1) ? (CoinChangerOptions.EnableExtOptionsBits | 2) : (CoinChangerOptions.EnableExtOptionsBits & 0xfd);
	CoinChangerOptions.EnableExtOptionsBits = (ControlledManualFillAndPayout == 1) ? (CoinChangerOptions.EnableExtOptionsBits | 4) : (CoinChangerOptions.EnableExtOptionsBits & 0xfb);
	CoinChangerOptions.EnableExtOptionsBits |= (0 << 3);
	WriteCoinChangerOptions();
	EXT_UART_Transmit_S("CC*FEATCFG*");
	EXT_UART_OK();
	CoinChangerEnableFeatures();
}

void CoinChangerEnableFeatures()
{
	EXT_UART_Transmit_S("CC*FEATENABLE*");
	uint8_t cmd[7];
	cmd[0] = 0x0f;
	cmd[1] = 0x01;
	cmd[2] = 0x00;
	cmd[3] = 0x00;
	cmd[4] = 0x00;
	cmd[5] = CoinChangerOptions.EnableExtOptionsBits;
	cmd[6] = ((cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4] + cmd[5]) & 0xff);
	MDB_Send(cmd, 7);
	while (!MDBReceiveComplete){
		MDB_read();
	}
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		CoinChangerDevice.OfflinePollsCount = 5;
		if (MDB_RESPONSE_TYPE == MDB_RESP_ACK)
		{
			EXT_UART_OK();
			return;
		}
	}
	EXT_UART_FAIL();
	if (CoinChangerDevice.OfflinePollsCount > 0) CoinChangerDevice.OfflinePollsCount--;
}

void GetCoinChangerIdentification()
{
	uint8_t cmd[3] = {0x0f, 0x00, 0x0f};
	MDB_Send(cmd,3);
	while (!MDBReceiveComplete)
	{
		MDB_read();
	}
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		if (MDB_BUFFER_COUNT > 0)
		{
			MDB_ACK();
			CoinChangerDevice.OfflinePollsCount = 5;
			uint8_t tmpstr[64];
			for (int i = 0; i < 3; i++)
			{
				CoinChangerIDData.ManufacturerCode[i] = 0x00;
			}
			for (int i = 0; i < 12; i++)
			{
				CoinChangerIDData.SerialNumber[i] = 0x00;
			}
			for (int i = 0; i < 12; i++)
			{
				CoinChangerIDData.ModelRevision[i] = 0x00;
			}
			uint8_t tmpmfg[3] = {MDB_BUFFER[0], MDB_BUFFER[1], MDB_BUFFER[2]};
			memcpy(CoinChangerIDData.ManufacturerCode, tmpmfg, 3);
			EXT_UART_Transmit_S("CC*ID*");
			EXT_UART_Transmit(CoinChangerIDData.ManufacturerCode);
			uint8_t tmpsn[12] = {MDB_BUFFER[3], MDB_BUFFER[4], MDB_BUFFER[5], MDB_BUFFER[6], MDB_BUFFER[7], MDB_BUFFER[8], MDB_BUFFER[9], MDB_BUFFER[10], MDB_BUFFER[11], MDB_BUFFER[12], MDB_BUFFER[13], MDB_BUFFER[14]};
			memcpy(CoinChangerIDData.SerialNumber,tmpsn, 12);
			EXT_UART_Transmit_S("*");
			EXT_UART_Transmit(CoinChangerIDData.SerialNumber);
			uint8_t tmpmr[12] = {MDB_BUFFER[15], MDB_BUFFER[16], MDB_BUFFER[17], MDB_BUFFER[18], MDB_BUFFER[19], MDB_BUFFER[20], MDB_BUFFER[21], MDB_BUFFER[22], MDB_BUFFER[23], MDB_BUFFER[24], MDB_BUFFER[25], MDB_BUFFER[26]};
			memcpy(CoinChangerIDData.ModelRevision,tmpmr, 12);
			EXT_UART_Transmit_S("*");
			EXT_UART_Transmit(CoinChangerIDData.ModelRevision);
			uint8_t srd[2] = {MDB_BUFFER[27], MDB_BUFFER[28]};
			CoinChangerIDData.SoftwareVersion = BCDByteToInt(srd, sizeof(srd));
			if (MDB_BUFFER_COUNT >= 33)
			{
				uint32_t flags  = MDB_BUFFER[29];
				flags = (flags << 8) | MDB_BUFFER[30];
				flags = (flags << 8) | MDB_BUFFER[31];
				flags = (flags << 8) | MDB_BUFFER[32];
				CoinChangerIDData.AlternativePayout = ((flags & (1 << 0)) != 0);
				CoinChangerIDData.ExtendedDiagnostic = ((flags & (1 << 1)) != 0);
				CoinChangerIDData.ControlledManualFillAndPayout = ((flags & (1 << 2)) != 0);
				CoinChangerIDData.FTLSupported = ((flags & (1 << 3)) != 0);
			}
			XXXX_sprintf_FSTR((char*)tmpstr,"*%d*%d*%d*%d*%d", CoinChangerIDData.SoftwareVersion, CoinChangerIDData.AlternativePayout, CoinChangerIDData.ExtendedDiagnostic, CoinChangerIDData.ControlledManualFillAndPayout, CoinChangerIDData.FTLSupported);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
		} else
		{
			if (MDB_BUFFER[0] == 0x00){

			}
		}
	} else
	{
		if (CoinChangerDevice.OfflinePollsCount > 0) CoinChangerDevice.OfflinePollsCount--;
	}
}

// Decode and output one diagnostic status pair (2 bytes)
static void ProcessCCDiagPair(uint8_t byte0, uint8_t byte1)
{
	uint8_t statusvaluebytes[2] = {byte0, byte1};
	uint16_t statusvalue = BCDByteToInt(statusvaluebytes, sizeof(statusvaluebytes));
	char msg[16];
	XXXX_sprintf_FSTR(msg,"%s*%02x%02x", "UNK", byte0, byte1);

	if ((statusvalue != 510) && CoinChangerInManualFillOrPaymentMode)
	{
		CoinChangerInManualFillOrPaymentMode = 0;
		CoinChangerControlledManualFillReport();
	}

	// BCD-based status codes
	switch (statusvalue)
	{
		case 100: sprintf(msg,"%s", "POWERUP"); break;
		case 200: sprintf(msg,"%s", "POWERDOWN"); break;
		case 300: sprintf(msg,"%s", "OK"); break;
		case 400: sprintf(msg,"%s", "KEYPADSHIFTED"); break;
		case 510:
			sprintf(msg,"%s", "MANUALFILLPAY");
			if (CoinChangerInManualFillOrPaymentMode != 1) CoinChangerInManualFillOrPaymentMode = 1;
			break;
		case 520: sprintf(msg,"%s", "NEWINVENTORY"); break;
		case 600: sprintf(msg,"%s", "INHIBITED"); break;
	}

	// Module-specific error codes (byte0 = module, byte1 = detail)
	switch (byte0)
	{
		case 0x10: // General changer error
			switch (byte1)
			{
				case 0x00: sprintf(msg,"%s", "ERROR"); break;
				case 0x01: sprintf(msg,"%s", "CSERR1"); break;
				case 0x02: sprintf(msg,"%s", "CSERR2"); break;
				case 0x03: sprintf(msg,"%s", "LOWVOLTAGE"); break;
			}
			break;
		case 0x11: // Discriminator module error
			switch (byte1)
			{
				case 0x00: sprintf(msg,"%s", "DISCERR"); break;
				case 0x10: sprintf(msg,"%s", "DISCDECK"); break;
				case 0x11: sprintf(msg,"%s", "DISCOPN"); break;
				case 0x30: sprintf(msg,"%s", "DISCJAM"); break;
				case 0x41: sprintf(msg,"%s", "DISCBLSTD"); break;
				case 0x50: sprintf(msg,"%s", "DISCASENS"); break;
				case 0x51: sprintf(msg,"%s", "DISCBSENS"); break;
				case 0x52: sprintf(msg,"%s", "DISCCSENS"); break;
				case 0x53: sprintf(msg,"%s", "DISCTMP"); break;
				case 0x54: sprintf(msg,"%s", "DISCOPT"); break;
			}
			break;
		case 0x12: // Accept gate module error
			switch (byte1)
			{
				case 0x00: sprintf(msg,"%s", "GATERR"); break;
				case 0x30: sprintf(msg,"%s", "GATNX"); break;
				case 0x31: sprintf(msg,"%s", "GATALM"); break;
				case 0x40: sprintf(msg,"%s", "GATND"); break;
				case 0x50: sprintf(msg,"%s", "GATSENS"); break;
			}
			break;
		case 0x13: // Separator module error
			switch (byte1)
			{
				case 0x00: sprintf(msg,"%s", "SEPERR"); break;
				case 0x10: sprintf(msg,"%s", "SEPSENS"); break;
			}
			break;
		case 0x14: // Dispenser module error
			switch (byte1)
			{
				case 0x00: sprintf(msg,"%s", "DISPERR"); break;
			}
			break;
		case 0x15: // Coin cassette/tube module error
			switch (byte1)
			{
				case 0x00: sprintf(msg,"%s", "CASERR"); break;
				case 0x02: sprintf(msg,"%s", "CASRMD"); break;
				case 0x03: sprintf(msg,"%s", "CASSENS"); break;
				case 0x04: sprintf(msg,"%s", "CASLIT"); break;
			}
			break;
	}

	EXT_UART_Transmit_S("CC*DIAG*");
	EXT_UART_Transmit_S(msg);
	EXT_CRLF();
}

void GetCoinChangerDiagnosticStatus()
{
	//EXPANSION SEND DIAG STATUS � 0F 05h 
	uint8_t cmd[3] = {0x0f, 0x05, 0x14}; // 0FH EXPANSION COMMAND / SEND DIAGNOSTIC STATUS + 0x14 CHECK 
	MDB_Send(cmd,3);
	while (!MDBReceiveComplete)
	{
		MDB_read();
	}
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		if (MDB_RESPONSE_TYPE == MDB_RESP_ACK)
		{
			EXT_UART_Transmit_S("CC*DIAG*OK");
			EXT_CRLF();
			CoinChangerDevice.OfflinePollsCount = 5;
		}
		else if (MDB_RESPONSE_TYPE == MDB_RESP_NAK)
		{
			EXT_UART_Transmit_S("CC*DIAG*NAK");
			EXT_CRLF();
		}
		else if (MDB_RESPONSE_TYPE == MDB_RESP_DATA && MDB_BUFFER_COUNT >= 2 && ((MDB_BUFFER_COUNT % 2) == 0))
		{
			MDB_ACK();
			CoinChangerDevice.OfflinePollsCount = 5;
			uint16_t tmplen = MDB_BUFFER_COUNT;
			uint8_t TMP[tmplen];
			memcpy(TMP, MDB_BUFFER, MDB_BUFFER_COUNT);

			EXT_UART_Transmit_HEXDUMP("DIAGST", TMP, MDB_BUFFER_COUNT);
			for (int i = 0; i < tmplen - 1; i += 2)
			{
				ProcessCCDiagPair(TMP[i], TMP[i + 1]);
			}
		}
		else if (MDB_RESPONSE_TYPE == MDB_RESP_DATA)
		{
			EXT_UART_Transmit_HEXDUMP("CC*DIAG*BADDATA", MDB_BUFFER, MDB_BUFFER_COUNT);
		}
		else
		{
			EXT_UART_UNK();
		}
	} else
	{
		EXT_UART_Transmit_S("CC*DIAG*ND");
		EXT_CRLF();
		if (CoinChangerDevice.OfflinePollsCount > 0) CoinChangerDevice.OfflinePollsCount--;
	}
}

void CoinChangerControlledManualFillReport()
{
	uint8_t cmd[3];
	cmd[0] = 0x0f;
	cmd[1] = 0x06;
	cmd[2] = 0x15;
	MDB_Send(cmd, 3);
	while (!MDBReceiveComplete){
		MDB_read();
	}
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		if (MDB_BUFFER_COUNT > 0)
		{
			MDB_ACK();
			CoinChangerDevice.OfflinePollsCount = 5;
			for (int i = 0; i < MDB_BUFFER_COUNT; i++)
			{
				if (MDB_BUFFER[i] > 0)
				{
					uint8_t tmpstr[10 + CoinChangerSetupData.DecimalPlaces];
					EXT_UART_Transmit_S("CC*MANUALFILL");
					uint8_t buff[5 + CoinChangerSetupData.DecimalPlaces];
					double coinvalue = (CoinChangerSetupData.CoinScalingFactor * CoinChangerSetupData.CoinTypeCredit[i]) / pow(10, CoinChangerSetupData.DecimalPlaces);
					dtostrf(coinvalue,0,CoinChangerSetupData.DecimalPlaces,(char*)buff);
					sprintf((char*)tmpstr,"*%s", buff);
					EXT_UART_Transmit_S((char*)tmpstr);
					XXXX_sprintf_FSTR((char*)buff,"*%d", MDB_BUFFER[i]);
					EXT_UART_Transmit(buff);
					EXT_CRLF();
				}
			}
			//GetCoinChangerTubeStatus();
		} else
		{
			EXT_UART_Transmit_S("CC*MANUALFILL*UNKNOWN");
			EXT_CRLF();
		}
	} else
	{
		EXT_UART_Transmit_S("CC*MANUALFILL*FAIL");
		EXT_CRLF();
		if (CoinChangerDevice.OfflinePollsCount > 0) CoinChangerDevice.OfflinePollsCount--;
	}
	CoinChangerControlledManualPayoutReport();
}

void CoinChangerControlledManualPayoutReport()
{
	uint8_t cmd[3];
	cmd[0] = 0x0f;
	cmd[1] = 0x07;
	cmd[2] = 0x16;
	MDB_Send(cmd, 3);
	while (!MDBReceiveComplete){
		MDB_read();
	}
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		if (MDB_BUFFER_COUNT > 0)
		{
			MDB_ACK();
			CoinChangerDevice.OfflinePollsCount = 5;
			for (int i = 0; i < MDB_BUFFER_COUNT; i++)
			{
				if (MDB_BUFFER[i] > 0)
				{
					uint8_t tmpstr[10 + CoinChangerSetupData.DecimalPlaces];
					EXT_UART_Transmit_S("CC*MANUALPAYOUT");
					uint8_t buff[5 + CoinChangerSetupData.DecimalPlaces];
					double coinvalue = (CoinChangerSetupData.CoinScalingFactor * CoinChangerSetupData.CoinTypeCredit[i]) / pow(10, CoinChangerSetupData.DecimalPlaces);
					dtostrf(coinvalue,0,CoinChangerSetupData.DecimalPlaces,(char*)buff);
					sprintf((char*)tmpstr,"*%s", buff);
					EXT_UART_Transmit_S((char*)tmpstr);
					XXXX_sprintf_FSTR((char*)buff,"*%d", MDB_BUFFER[i]);
					EXT_UART_Transmit(buff);
					EXT_CRLF();
				}
			}
			//GetCoinChangerTubeStatus();
		} else
		{
			EXT_UART_Transmit_S("CC*MANUALPAYOUT*UNKNOWN");
			EXT_CRLF();
		}
	} else
	{
		EXT_UART_Transmit_S("CC*MANUALPAYOUT*FAIL");
		EXT_CRLF();
		if (CoinChangerDevice.OfflinePollsCount > 0) CoinChangerDevice.OfflinePollsCount--;
	}
}