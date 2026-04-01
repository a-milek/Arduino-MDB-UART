/*
 * Cashless_M.c
 *
 * Created: 18.05.2019 10:07:59
 *  Author: root
 */ 
#include "utils.h"
#include "config.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include "MDB_M.h"
#include "Settings_M.h"
#include "USART_M.h"
#include "Cashless_M.h"
#include "config.h"
#include "LEDControl_M.h"
#include <stdlib.h>

#include "myflash.h"

cdiddata ReaderIDData[2];
cdsetupdata ReaderSetupData[2];
mdbdevice CashlessDevice[2];

#define Z1  1
#define Z2  2
#define Z3  3
#define Z4  4
#define Z5  5
#define Z6  6
#define Z7  7


//
// 7.4.2 SETUP - Config Data
// 
// b'DIAG:MDBSEND:1100 03 10 02 01 27\r\n'
//
// response: b'CD1*CFG1*3*268*1*2*89*1*1*1*1\r\n'
//
// b'DIAG:MDBSEND:1100 03 10 02 01 27\r\n'


void CashlessDeviceSetup(uint8_t index)
{
	uint8_t tmpstr[80];
	uint8_t cmd[7];
	if (!index)
	{
		cmd[0] = 0x11;
	} else
	{
		cmd[0] = 0x61;
	}
	cmd[1] = 0x00;
	cmd[2] = VMCData.VMC_FEATURE_LEVEL;
	cmd[3] = VMCData.VMC_DISPLAY_COLUMNS;
	cmd[4] = VMCData.VMC_DISPLAY_ROWS;
	cmd[5] = VMCData.VMC_DISPLAY_TYPE;
	cmd[6] = (cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4] + cmd[5]) & 0xff;
	MDB_Send(cmd, 7);
	while (!MDBReceiveComplete){
		MDB_read();
	}
	//uint8_t * buff[6];
	//sprintf(buff, "%d\r\n", MDB_BUFFER_COUNT);
	//EXT_UART_Transmit(buff);
	//for (int a = 0; a < MDB_BUFFER_COUNT - 1; a++){
	//sprintf(&buff, "%02x ", MDB_BUFFER[a].data);
	//EXT_UART_Transmit(buff);
	//}
	//sprintf(&buff, "%02x ", MDB_BUFFER[MDB_BUFFER_COUNT - 1].data);
	//EXT_UART_Transmit(buff);
	//EXT_CRLF();
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		if (MDB_BUFFER_COUNT > 1)
		{
			MDB_ACK();
			CDLED_ON(index);
			EXT_UART_Transmit_HEXDUMP_MDBBYTE("DEVSETUP", MDB_BUFFER, MDB_BUFFER_COUNT);
			ProcessReaderConfig(index, 0);
			if (ReaderIDData[index].Monetary32bitSupported || ReaderIDData[index].MultiCurrencySupported)
			{
				
			}
		}
		if (MDB_BUFFER_COUNT == 1)
		{
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*CONFIG*", index + 1);
			EXT_UART_Transmit_S((char*)tmpstr);
			if (MDB_BUFFER[0].data == 0x00 && MDB_BUFFER[0].mode)
			{
				EXT_UART_OK();
			} else
			{
				EXT_UART_NAK();
			}
			//return;
		}
	} else
	{
		XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*CONFIG*", index + 1);
		EXT_UART_Transmit_S((char*)tmpstr);
		EXT_UART_FAIL();
		CDLED_OFF(index);
	}
	//ProcessReaderConfig();
	//ReaderProcessResponse(index, "CONFIG");
}

void CashlessDeviceSetupPrices16bit(uint8_t index)
{
	uint8_t tmpstr[64];
	uint8_t cmd[7];
	cmd[0] = (index) ? 0x61 : 0x11;
	cmd[1] = 0x01;
	cmd[2] = ReaderOptions[index].MaxPrice.Bytes[0];
	cmd[3] = ReaderOptions[index].MaxPrice.Bytes[1];
	cmd[4] = ReaderOptions[index].MinPrice.Bytes[0];
	cmd[5] = ReaderOptions[index].MinPrice.Bytes[1];
	cmd[6] = (cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4] + cmd[5]) & 0xff;
	MDB_Send(cmd, 7);
	while (!MDBReceiveComplete){
		MDB_read();
	}
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		CDLED_ON(index);
		if (MDB_BUFFER_COUNT == 1)
		{
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*CFGPRICE1*", index + 1);
			EXT_UART_Transmit_S((char*)tmpstr);
			if (MDB_BUFFER[0].data == 0x00 && MDB_BUFFER[0].mode)
			{
				EXT_UART_OK();
			} else
			{
				EXT_UART_NAK();
			}
		}
	} else
	{
		XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*CFGPRICE1*", index + 1);
		EXT_UART_Transmit_S((char*)tmpstr);
		EXT_UART_FAIL();
		CDLED_OFF(index);
	}
}


static uint8_t mdb_cmd_sum(uint8_t cmd[], size_t cmd_data_index) {
	uint8_t sum = 0;
	for(size_t k = 0; k <= cmd_data_index; k++) {
		sum += cmd[k];
	}
	return sum;
}

// 7.4.3 SETUP � Max / Min Prices
void CashlessDeviceSetupPrices32bit(uint8_t index)
{
	uint8_t tmpstr[64];
	
	
	if (ReaderOptions[index].ReaderOptFeatures.MonetaryFormat32bitEnabled == 0)  {
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*CFGPRICE2*FL_LOW", index + 1);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
			return;
	}
	
	
	uint8_t cmd[13];
	if (!index)
	{
		cmd[0] = 0x11;
	} else
	{
		cmd[0] = 0x61;
	}
	cmd[1] = 0x01;
	cmd[2] = ReaderOptions[index].MaxPrice.Bytes[0];
	cmd[3] = ReaderOptions[index].MaxPrice.Bytes[1];
	cmd[4] = ReaderOptions[index].MaxPrice.Bytes[2];
	cmd[5] = ReaderOptions[index].MaxPrice.Bytes[3];
	cmd[6] = ReaderOptions[index].MinPrice.Bytes[0];
	cmd[7] = ReaderOptions[index].MinPrice.Bytes[1];
	cmd[8] = ReaderOptions[index].MinPrice.Bytes[2];
	cmd[9] = ReaderOptions[index].MinPrice.Bytes[3];
	cmd[10] = ReaderOptions[index].CountryOrCurrencyCode[0];
	cmd[11] = ReaderOptions[index].CountryOrCurrencyCode[1];
	
	cmd[12] = (cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4] + cmd[5] + cmd[6] + cmd[7] + cmd[8] + cmd[9] + cmd[10] + cmd[11]) & 0xff;
	MDB_Send(cmd, 13);
	while (!MDBReceiveComplete){
		MDB_read();
	}
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		CDLED_ON(index);
		if (MDB_BUFFER_COUNT == 1)
		{
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*CFGPRICE2*", index + 1);
			EXT_UART_Transmit_S((char*)tmpstr);
			if (MDB_BUFFER[0].data == 0x00 && MDB_BUFFER[0].mode)
			{
				EXT_UART_OK();
			} else
			{
				EXT_UART_NAK();
			}
		}
	} else
	{
		XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*CFGPRICE2*", index + 1);
		EXT_UART_Transmit_S((char*)tmpstr);
		EXT_UART_FAIL();
		CDLED_OFF(index);
	}
}

void CashlessDeviceRequestExpansionID(uint8_t index)
{
	uint8_t tmpstr[64];
	uint8_t cmd[32];
	cmd[0] = (index) ? 0x67 : 0x17;
	cmd[1] = 0x00;
	uint16_t mdbsum = cmd[0] + cmd[1];
	for (int i = 2; i < 5; i++)
	{
		cmd[i] = VMCData.VMCMfgCode[i - 2];
		mdbsum += cmd[i];
	}
	for (int i = 5; i < 17; i++)
	{
		cmd[i] = VMCData.VMCSerialNumber[i - 5];
		mdbsum += cmd[i];
	}
	for (int i = 17; i < 29; i++)
	{
		cmd[i] = VMCData.VMCModelNumber[i - 17];
		mdbsum += cmd[i];
	}
	for (int i = 29; i < 31; i++)
	{
		cmd[i] = VMCData.VMCSofwareVersion[i - 29];
		mdbsum += cmd[i];
	}
	cmd[31] = mdbsum & 0xff;
	MDB_Send(cmd, 32);
	while (!MDBReceiveComplete){
		MDB_read();
	}
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		if (MDB_BUFFER_COUNT > 1)
		{
			MDB_ACK();
			CDLED_ON(index);
			ProcessReaderExpID(index, MDB_BUFFER, MDB_BUFFER_COUNT);
			//return;
			
		}
		if (MDB_BUFFER_COUNT == 1)
		{
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*EXPIDREQ*", index + 1);
			EXT_UART_Transmit_S((char*)tmpstr);
			if (MDB_BUFFER[0].data == 0x00 && MDB_BUFFER[0].mode)
			{
				EXT_UART_OK();
			} else
			{
				EXT_UART_NAK();
			}
		}
	} else
	{
		XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*EXPIDREQ*", index + 1);
		EXT_UART_Transmit_S((char*)tmpstr);
		EXT_UART_FAIL();
		CDLED_OFF(index);
	}
}

//
// 7.4.24 EXPANSION � Enable Options (Level 03 readers)
void CashlessDeviceEnableOptFetures(uint8_t index)
{
	const uint8_t AskBeginSession = 0;
	uint8_t tmpstr[64];
	if (ReaderSetupData[index].ReaderFeatureLevel == 3)
	{
		uint8_t cmd[7];
		cmd[0] = (index) ? 0x67 : 0x17;
		cmd[1] = 0x04;
		cmd[2] = 0x00;
		cmd[3] = 0x00;
		cmd[4] = 0x00 | 
		(
		  (AskBeginSession == 1) << (9-8)
		 );
		//Enable all supported features
		cmd[5] = 0x00 | 
		(
		 (((ReaderIDData[index].FTLSupported & ReaderOptions[index].ReaderOptFeatures.FTLEnabled) == 1) << 0) |
		 (((ReaderIDData[index].Monetary32bitSupported & ReaderOptions[index].ReaderOptFeatures.MonetaryFormat32bitEnabled) == 1) << 1) |
		 (((ReaderIDData[index].MultiCurrencySupported & ReaderOptions[index].ReaderOptFeatures.MultiCurrEnabled) == 1) << 2) |
		 (((ReaderIDData[index].NVendSupported & ReaderOptions[index].ReaderOptFeatures.NegVendEnabled) == 1) << 3) |
		 (((ReaderIDData[index].DataEntrySupported & ReaderOptions[index].ReaderOptFeatures.DataEntryEnabled) == 1) << 4) |
		 (((ReaderIDData[index].AlwaysIdleSupported & ReaderOptions[index].ReaderOptFeatures.AlwaysIdleEnabled) == 1) << 5)
		 );
		//cmd[5] = 0x38;
		cmd[6] = (cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4] + cmd[5]) & 0xff;
		MDB_Send(cmd, 7);
		while (!MDBReceiveComplete){
			MDB_read();
		}
		if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
		{
			CDLED_ON(index);
			if (MDB_BUFFER_COUNT == 1)
			{
				XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*ENFEAT*", index + 1);
				EXT_UART_Transmit_S((char*)tmpstr);
				if (MDB_BUFFER[0].data == 0x00 && MDB_BUFFER[0].mode)
				{
					EXT_UART_OK();
				} else
				{
					EXT_UART_NAK();
				}
			}
		} else
		{
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*ENFEAT*", index + 1);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_UART_FAIL();
		}
	} else
	{
		uint8_t tmpstr[32];
		XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*ENFEAT*FL_LOW", index + 1);
		EXT_UART_Transmit_S((char*)tmpstr);
		EXT_CRLF();
		CDLED_OFF(index);
	}
}

// WM: produces CFG2*NYX*000000406783*DMX - 2011  d*100*0*0*0*0*0*0\r\n'
// WM: NYX - ManufacturerCode - 3*char
// WM: 000000406783 - SerialNumber 12*char
// WM: "DMX - 2011  d" - Z17-Z28 ModelRevision / Model Number 12*char (corrected now b'CD1*CFG2*NYX*000000406783*DMX - 2011  *100*0*0*0*0*0*0\r\n'
void ProcessReaderExpID(uint8_t index, MDB_Byte expiddata[], size_t expiddata_count)
{
	
		
	if (1) {
		char tmpstr[32];
		sprintf((char*)tmpstr,"WMDIAG*:%d", expiddata_count);
		EXT_UART_Transmit_S((char*)tmpstr);
		EXT_UART_Transmit_HEXDUMP_MDBBYTE("EXPID", expiddata, expiddata_count);
	}

	uint8_t tmpstr[32];
	ReaderIDData[index].ManufacturerCode[0] = 0x00;
	ReaderIDData[index].SerialNumber[0] = 0x00;
	ReaderIDData[index].ModelRevision[0] = 0x00;
	uint8_t tmpmfg[3] = {expiddata[1].data, expiddata[2].data, expiddata[3].data};
	memcpy(&ReaderIDData[index].ManufacturerCode, &tmpmfg, 3);
	XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*CFG2*", index + 1);
	EXT_UART_Transmit_S((char*)tmpstr);
	EXT_UART_Transmit_UN(ReaderIDData[index].ManufacturerCode, sizeof (ReaderIDData[index].ManufacturerCode));
	uint8_t tmpsn[12] = {expiddata[4].data, expiddata[5].data, expiddata[6].data, expiddata[7].data, expiddata[8].data, expiddata[9].data, expiddata[10].data, expiddata[11].data, expiddata[12].data, expiddata[13].data, expiddata[14].data, expiddata[15].data};
	memcpy(&ReaderIDData[index].SerialNumber,&tmpsn, 12);
	EXT_UART_Transmit_S("*");
	EXT_UART_Transmit_UN(ReaderIDData[index].SerialNumber, sizeof (ReaderIDData[index].SerialNumber));
	uint8_t tmpmr[12] = {expiddata[16].data, expiddata[17].data, expiddata[18].data, expiddata[19].data, expiddata[20].data, expiddata[21].data, expiddata[22].data, expiddata[23].data, expiddata[24].data, expiddata[25].data, expiddata[26].data, expiddata[27].data};
	memcpy(&ReaderIDData[index].ModelRevision,&tmpmr, 12);
	EXT_UART_Transmit_S("*");
	EXT_UART_Transmit_UN(ReaderIDData[index].ModelRevision, sizeof (ReaderIDData[index].ModelRevision));
	EXT_UART_Transmit_S("*");
	uint8_t srd[2] = {expiddata[28].data, expiddata[29].data};
	ReaderIDData[index].SoftwareVersion = BCDByteToInt(srd,sizeof(srd));
	if (expiddata_count == 35)
	{
		const size_t _Z34 = 34 - 1;
		ReaderIDData[index].FTLSupported = ((expiddata[_Z34].data & (1 << 0)) != 0);
		ReaderIDData[index].Monetary32bitSupported = ((expiddata[_Z34].data & (1 << 1)) != 0);
		ReaderIDData[index].MultiCurrencySupported = ((expiddata[_Z34].data & (1 << 2)) != 0);
		ReaderIDData[index].NVendSupported = ((expiddata[_Z34].data & (1 << 3)) != 0);
		ReaderIDData[index].DataEntrySupported = ((expiddata[_Z34].data & (1 << 4)) != 0);
		ReaderIDData[index].AlwaysIdleSupported = ((expiddata[_Z34].data & (1 << 5)) != 0);
	}
	XXXX_sprintf_FSTR((char*)tmpstr,"%d*%d*%d*%d*%d*%d*%d\r\n", ReaderIDData[index].SoftwareVersion, ReaderIDData[index].FTLSupported, ReaderIDData[index].Monetary32bitSupported, ReaderIDData[index].MultiCurrencySupported, ReaderIDData[index].NVendSupported, ReaderIDData[index].DataEntrySupported, ReaderIDData[index].AlwaysIdleSupported);
	EXT_UART_Transmit_S((char*)tmpstr);
}

//
// WM: 7.4.4 POLL
// WM: Reader Config Info (01H) Z1
// WM: 7.4.2 SETUP - Config Data - description of Miscellaneous Options
// e: b'CD1*CFG1*3*268*1*2*89*1*1*1*1\r\n'
// WM b'CD1*CFG1*3*268*1*2*120*1*1*1*1\r\n'
//               ^ level  
//                  ^ country code 268 -> 0x010c leftmost is 0-> the International Telephone ?? 
//                     ^ - ScalingFactor
//                       ^ - DecimalPlaces 2
//                         ^ - MaxResponseTime


//    b'CD1*CFG1*1*268*1*2*89*1*1*1*1\r\n'
  

void ProcessReaderConfig(uint8_t index, uint8_t startindex)
{
	uint8_t tmpstr[80];
	
	if ( MDB_BUFFER[startindex + 1].data < 0x01 || MDB_BUFFER[startindex + 1].data > 0x03) {
		XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*CFG1*???", index + 1);
		EXT_UART_Transmit_S((char*)tmpstr);
		EXT_CRLF();
		return;
	}
	
	ReaderSetupData[index].ReaderFeatureLevel = MDB_BUFFER[startindex + 1].data;
	ReaderSetupData[index].CountryOrCurrencyCode[0] = MDB_BUFFER[startindex + 2].data;
	ReaderSetupData[index].CountryOrCurrencyCode[1] = MDB_BUFFER[startindex + 3].data;
	ReaderSetupData[index].ScalingFactor = MDB_BUFFER[startindex + 4].data;
	ReaderSetupData[index].DecimalPlaces = MDB_BUFFER[startindex + 5].data;
	ReaderSetupData[index].MaxResponseTime = MDB_BUFFER[startindex + 6].data;
	ReaderSetupData[index].Refundable = ((MDB_BUFFER[startindex + 7].data & (1 << 0)) != 0);
	ReaderSetupData[index].Multivend = ((MDB_BUFFER[startindex + 7].data & (1 << 1)) != 0); // 1 - The payment media reader is multivend capable. Multiple items may be purchased within a single session.
	ReaderSetupData[index].DisplayAvailable = ((MDB_BUFFER[startindex + 7].data & (1 << 2)) != 0);
	ReaderSetupData[index].VendCashSaleSupport = ((MDB_BUFFER[startindex + 7].data & (1 << 3)) != 0);
	uint16_t usercountrycode = BCDByteToInt(ReaderSetupData[index].CountryOrCurrencyCode, sizeof(ReaderSetupData[index].CountryOrCurrencyCode));
	XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*CFG1*%d*%d*%d*%d*%d*%d*%d*%d*%d", index + 1, ReaderSetupData[index].ReaderFeatureLevel, usercountrycode, ReaderSetupData[index].ScalingFactor, \
	ReaderSetupData[index].DecimalPlaces, ReaderSetupData[index].MaxResponseTime, ReaderSetupData[index].Refundable, ReaderSetupData[index].Multivend, ReaderSetupData[index].DisplayAvailable, ReaderSetupData[index].VendCashSaleSupport);
	EXT_UART_Transmit_S((char*)tmpstr);
	EXT_CRLF();
}

void ProcessReaderVendApproved(uint8_t index, MDB_Byte vendappdata[], size_t vendappdata_size )
{
	uint8_t buff[10 + ReaderSetupData[index].DecimalPlaces];
	uint8_t tmpstr[32];
	uint32_t availablefundsdata;
	if (vendappdata_size == 10)
	{
		availablefundsdata = (uint32_t)vendappdata[1].data << 24 | ((uint32_t)vendappdata[2].data << 16) | ((uint32_t)vendappdata[3].data << 8) | ((uint32_t)vendappdata[4].data);
	}
	else if (vendappdata_size == 6)
	{
		availablefundsdata = (uint32_t)vendappdata[1].data << 8 | (uint32_t)vendappdata[2].data;
	}
	else{
		availablefundsdata=0xFFFFFF; //FIXME!
	}
	dtostrf(availablefundsdata / pow(10, ReaderSetupData[index].DecimalPlaces),0,ReaderSetupData[index].DecimalPlaces,(char*)buff);
	XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*VAPPR*%s", index + 1, buff);
	EXT_UART_Transmit_S((char*)tmpstr);
	EXT_CRLF();
}

// WM: b'DIAG:RPR:0307d036373833000000b2\r\n'

void ProcessReaderSessionBegin(uint8_t index, MDB_Byte sbdata[], size_t sbsize)
{
	uint8_t buff[10 + ReaderSetupData[index].DecimalPlaces];
	uint8_t tmpstr[32];
	unsigned long availablefundsdata;
	
	
	if (1) {
		char tmpdbgstr[32];
		sprintf(tmpdbgstr,"WMDIAG:sbsize:%d", sbsize);
		EXT_UART_Transmit_S(tmpdbgstr);
		EXT_UART_Transmit_HEXDUMP("SBDATA", sbdata, sbsize);
	}


	switch (sbsize)
	{
		case 34:
		{
			uint32_t availablefundsdata = (uint32_t)sbdata[1].data << 24 | ((uint32_t)sbdata[2].data << 16) | ((uint32_t)sbdata[3].data << 8) | ((uint32_t)sbdata[4].data);
			
			dtostrf(availablefundsdata / pow(10, ReaderSetupData[index].DecimalPlaces),0,ReaderSetupData[index].DecimalPlaces,(char*)buff);
			uint8_t paymentmediaid[9];
			uint8_t paymenttype[16];
			switch (sbdata[9].data >> 6)
			{
				case 0:
				sprintf((char*)paymenttype,"%s","NORMAL");
				break;
				case 1:
				sprintf((char*)paymenttype,"%s","TEST");
				break;
				case 2:
				sprintf((char*)paymenttype,"%s","FREE");
				break;
				default:
				switch (sbdata[9].data & 0x3f)
				{
					case 0:
					sprintf((char*)paymenttype,"%s","VMCDP");
					break;
					case 1:
					XXXX_sprintf_FSTR((char*)paymenttype,"UG%d*PLN%d", sbdata[10].data, sbdata[11].data);
					break;
					case 2:
					XXXX_sprintf_FSTR((char*)paymenttype,"UG%d*DGI%d", sbdata[10].data, sbdata[11].data);
					break;
					case 3:
					XXXX_sprintf_FSTR((char*)paymenttype,"DISCP%d", sbdata[11].data);
					break;
					case 4:
					XXXX_sprintf_FSTR((char*)paymenttype,"SURCP%d", sbdata[11].data);
					break;
				}
				break;
			}
			XXXX_sprintf_FSTR((char*)paymentmediaid,"%02x%02x%02x%02x",sbdata[5].data,sbdata[6].data,sbdata[7].data,sbdata[8].data);
			uint8_t userlanguage[2] = {sbdata[12].data,sbdata[13].data};
			uint8_t usercountrycodedata[2] = {sbdata[14].data,sbdata[15].data};
			uint16_t usercountrycode =BCDByteToInt(usercountrycodedata, sizeof(usercountrycodedata));
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*SBEGIN*%s*%s*%s*%s*%d*%d*%d*%d", index + 1, buff, paymentmediaid, paymenttype, \
			userlanguage, usercountrycode, ((sbdata[16].data & (1 << 0)) == 0), ((sbdata[16].data & (1 << 1)) != 0), ((sbdata[16].data & (1 << 2)) != 0));
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
		}
		break;
		case 20: // WM BEGIN SESSION (level 02/03 readers)
		{
			availablefundsdata = sbdata[1].data << 8;
			availablefundsdata |= sbdata[2].data;
			dtostrf(availablefundsdata / pow(10, ReaderSetupData[index].DecimalPlaces),0,ReaderSetupData[index].DecimalPlaces,(char*)buff);
			uint8_t paymentmediaid[9];
			
			paymentmediaid[0] = sbdata[Z4 - 1].data;
			paymentmediaid[1] = sbdata[Z5 - 1].data;
			paymentmediaid[2] = sbdata[Z6 - 1].data;
			paymentmediaid[3] = sbdata[Z7 - 1].data;
			
			uint8_t paymenttype[16];
			switch (sbdata[7].data >> 6) // Z8 : Type of payment:
			{
				case 0:
				sprintf((char*)paymenttype,"%s","NORMAL");
				break;
				case 1:
				sprintf((char*)paymenttype,"%s","TEST");
				break;
				case 2:
				sprintf((char*)paymenttype,"%s","FREE");
				break;
				default:
				switch (sbdata[7].data & 0x3f)
				{
					case 0:
					sprintf((char*)paymenttype,"%s","VMCDP");
					break;
					case 1:
					XXXX_sprintf_FSTR((char*)paymenttype,"UG%d*PLN%d", sbdata[8].data, sbdata[9].data);
					break;
					case 2:
					XXXX_sprintf_FSTR((char*)paymenttype,"UG%d*DGI%d", sbdata[8].data, sbdata[9].data);
					break;
					case 3:
					XXXX_sprintf_FSTR((char*)paymenttype,"DISCP%d", sbdata[9].data);
					break;
					case 4:
					XXXX_sprintf_FSTR((char*)paymenttype,"SURCP%d", sbdata[9].data);
					break;
				}
				break;
			}
			XXXX_sprintf_FSTR((char*)paymentmediaid,"%02x%02x%02x%02x",sbdata[3].data,sbdata[4].data,sbdata[5].data,sbdata[6].data);
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*SBEGIN*%s*%s*%s", index + 1, buff, paymentmediaid, paymenttype);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
		}
		break;
		case 6: // WM BEGIN SESSION (level 01 readers)
		{
			availablefundsdata = sbdata[1].data << 8;
			availablefundsdata |= sbdata[2].data;
			dtostrf(availablefundsdata / pow(10, ReaderSetupData[index].DecimalPlaces),0,ReaderSetupData[index].DecimalPlaces,(char*)buff);
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*SBEGIN*%s", index + 1, buff);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
		}
		break;
		default:
		{
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*SBEGIN*ERROR_CANNOT_PARSE", index + 1);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
		}
		break;
	}
}

void ProcessReaderError(uint8_t index, MDB_Byte errdata[])
{
	uint8_t tmpstr[32];
	uint8_t error[8];
	switch (errdata[1].data >> 4)
	{
		case 0:
		sprintf((char*)error,"%s", "PMERR");
		break;
		case 1:
		sprintf((char*)error,"%s", "IPM");
		break;
		case 2:
		sprintf((char*)error,"%s", "TAMP");
		break;
		case 3:
		sprintf((char*)error,"%s", "MERR1");
		break;
		case 4:
		sprintf((char*)error,"%s", "COMERR");
		break;
		case 5:
		sprintf((char*)error,"%s", "SERV");
		break;
		case 6:
		sprintf((char*)error,"%s", "6");
		break;
		case 7:
		sprintf((char*)error,"%s", "MERR2");
		break;
		case 8:
		sprintf((char*)error,"%s", "RFAIL");
		break;
		case 9:
		sprintf((char*)error,"%s", "COMERR2");
		break;
		case 10:
		sprintf((char*)error,"%s", "PMJAM");
		break;
		case 11:
		sprintf((char*)error,"%s", "MERR3");
		break;
		case 12:
		sprintf((char*)error,"%s", "REFERR");
		break;
		default:
		sprintf((char*)error,"%s", "UNASGND");
		break;
	}
	XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*ERROR*%s*%d", index + 1, error, errdata[1].data & 0x0f);
	EXT_UART_Transmit_S((char*)tmpstr);
	EXT_CRLF();
}

void ReaderReset(uint8_t index)
{
	uint8_t addr = (index) ? 0x60 : 0x10;
	uint8_t cmd[2] = { addr, addr };
	MDB_Send(cmd, 2);
	ReaderProcessResponse(index, "RESET", NULL);
}

void ProcessReaderRevalueLimit(uint8_t index, MDB_Byte rlimdata[])
{
	uint32_t availablefundsdata;
	uint8_t tmpstr[32];
	uint8_t buff[10];
	if (sizeof(rlimdata) == 10)
	{
		availablefundsdata = (uint32_t)rlimdata[1].data << 24 | ((uint32_t)rlimdata[2].data << 16) | ((uint32_t)rlimdata[3].data << 8) | ((uint32_t)rlimdata[4].data);
	}
	else if (sizeof(rlimdata) == 6)
	{
		availablefundsdata = (uint32_t)rlimdata[1].data << 8 | (uint32_t)rlimdata[2].data;
	}
	else{
		availablefundsdata=0xFFFFFFF; //FIXME!
	}
	dtostrf(availablefundsdata / pow(10, ReaderSetupData[index].DecimalPlaces),0,ReaderSetupData[index].DecimalPlaces,(char*)buff);
	XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*REVLIMIT*%s", index + 1, buff);
	EXT_UART_Transmit_S((char*)tmpstr);
	EXT_CRLF();
}

// WM ref: 7.3.1 Multi-Message Response Format
void ReaderResponse(uint8_t index)
{
	uint8_t tmpstr[80];
	uint8_t dispbuff[32];
	//MDB_Byte tmpsetup[8];
	MDB_Byte tmpidlevel12[30];
	MDB_Byte tmpidlevel3[34];
	//uint8_t buff[16];
	uint16_t tmplen = MDB_BUFFER_COUNT;
	MDB_Byte TMP[tmplen];
	memcpy(&TMP, &MDB_BUFFER[0], MDB_BUFFER_COUNT * 2);
	for (int i = 0; i < tmplen - 1; i++)
	{
		if (1) {
			// WM: b'DIAG:RPR:0307d0da\r\n' - checksum hex(0x03 + 0x07 + 0xd0) = 0xda
			XXXX_sprintf_FSTR(tmpstr,"WMDIAG:CD%d*RR:i:%d/%d", index + 1, i, MDB_BUFFER_COUNT);
			EXT_UART_Transmit_S(tmpstr);
			EXT_CRLF();
		}
		switch (TMP[i].data)
		{
			case 0x00: // JUST RESET
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*JSTRST", index + 1);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
			CashlessDeviceSetup(index);
			CashlessDeviceSetupPrices16bit(index);
			CashlessDeviceRequestExpansionID(index);
			CashlessDeviceEnableOptFetures(index);
			CashlessDeviceSetupPrices32bit(index);
			
			return;
			case 0x01: // DISPLAY REQUEST
			//memcpy(&tmpsetup[0], &TMP[i], 16);
			ProcessReaderConfig(index, i);
			if (tmplen > 8) i += 7;
			break;
			case 0x02:
			for (int a = 2; a < 34; a++)
			{
				dispbuff[a - 2] = TMP[a].data;
			}
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*DISPREQ*%d*%s", index + 1, TMP[i + 1].data, dispbuff);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
			if (tmplen > 2) i++;
			return;
			case 0x03: // BEGIN SESSION (level 01 readers)
			
					XXXX_sprintf_FSTR((char*)tmpstr,"WMDIAG:CD%d*BS", index + 1);
					EXT_UART_Transmit_S((char*)tmpstr);
					EXT_CRLF();
			
			if (ReaderSetupData[index].ReaderFeatureLevel == 1)
			{
				MDB_Byte sbdata[3];
				memcpy(&sbdata, &TMP[i], 6);
				ProcessReaderSessionBegin(index,sbdata, sizeof sbdata);
				i += 3;
			} else if (ReaderSetupData[index].ReaderFeatureLevel >= 2) {
				//uint8_t buff[16];
				if (!(
				
						(ReaderSetupData[index].ReaderFeatureLevel == 3) && (ReaderOptions[index].ReaderOptFeatures.MonetaryFormat32bitEnabled || ReaderOptions[index].ReaderOptFeatures.MultiCurrEnabled))
						)
				{
					MDB_Byte sbdata[10];
					memcpy(&sbdata, &TMP[i], 20);
					ProcessReaderSessionBegin(index,sbdata, sizeof sbdata);
					i += 9;
				} else
				
				{
					MDB_Byte sbdata[17];
					memcpy(&sbdata, &TMP[i], 34);
					ProcessReaderSessionBegin(index,sbdata, sizeof sbdata);
					i += 16;
				}
			}
			break;
			case 0x04: // SESSION CANCEL REQUEST
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*SCANCREQ", index + 1);
			EXT_UART_Transmit_S((char*)tmpstr);
			
			EXT_CRLF();
			break;
			case 0x05: // VEND APROVED 
			{
				if ((ReaderSetupData[index].ReaderFeatureLevel == 3) && (ReaderOptions[index].ReaderOptFeatures.MonetaryFormat32bitEnabled || ReaderOptions[index].ReaderOptFeatures.MultiCurrEnabled))
				{
					MDB_Byte tmpvendappdata[5];
					memcpy(&tmpvendappdata, &TMP[i], 10);
					ProcessReaderVendApproved(index,tmpvendappdata, 10);
					i += 4;
				} else
				{
					MDB_Byte tmpvendappdata[3];
					memcpy(&tmpvendappdata, &TMP[i], 6);
					ProcessReaderVendApproved(index,tmpvendappdata, 6);
					i += 2;
				}
			}
			break;
			case 0x06: // VEND DENIED
			{
				//uint8_t * buff[6];
				//sprintf(buff, "%d\r\n", MDB_BUFFER_COUNT);
				//EXT_UART_Transmit(buff);
				//for (int a = 0; a < MDB_BUFFER_COUNT - 1; a++){
					//sprintf(&buff, "%02x ", MDB_BUFFER[a].data);
					//EXT_UART_Transmit(buff);
				//}
				//sprintf(&buff, "%02x ", MDB_BUFFER[MDB_BUFFER_COUNT - 1].data);
				//EXT_UART_Transmit(buff);
				//EXT_CRLF();
				XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*VDENY", index + 1);
				EXT_UART_Transmit_S((char*)tmpstr);
				EXT_CRLF();
			}
			if (tmplen > 2) i++;
			break;
			case 0x07: // END SESSION
			{
				XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*SEND", index + 1);
				EXT_UART_Transmit_S((char*)tmpstr);
				EXT_CRLF();
				
			}
			break;
			case 0x08: // CANCELLED - response on 7.4.16 READER - Cancel
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*CNCLD", index + 1);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
			break;
			case 0x09: // 09H - Peripheral ID
			if (VMCData.VMC_FEATURE_LEVEL == 3)
			{
				memcpy(&tmpidlevel3, &TMP[i], 68);
				ProcessReaderExpID(index, tmpidlevel3, ARRAY_SIZE(tmpidlevel3));
				i += 33;
			} else
			{
				memcpy(&tmpidlevel12, &TMP[i], 60);
				ProcessReaderExpID(index, tmpidlevel12, ARRAY_SIZE(tmpidlevel12));
				i += 29;
			}
			break;
			case 0x0a: // MALFUNCTION/ERROR
			{
				MDB_Byte errdata[2];
				memcpy(&errdata, &TMP[i], 4);
				ProcessReaderError(index,errdata);
				i ++;
			}
			break;
			case 0x0b: // COMMAND OUT OF SEQUENCE
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*COOS", index + 1);
			EXT_UART_Transmit(tmpstr);
			if (ReaderSetupData[index].ReaderFeatureLevel >= 2)
			{
				XXXX_sprintf_FSTR((char*)tmpstr,"*%d", TMP[i + 1].data);
				EXT_UART_Transmit_S((char*)tmpstr);
				CashlessDevice[index].Status = TMP[i + 1].data;
				i++;
			}
			EXT_CRLF();
			ReaderReset(index);
			return;
			case 0x0d: // REVALUE APPROVED
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*REVAPP", index + 1);
			EXT_UART_Transmit_S((char*)tmpstr);
			break;
			case 0x0e: // REVALUE DENIED
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*REVDENY", index + 1);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
			break;
			case 0x0f: // REVALUE LIMIT AMOUNT
			{
				if ((ReaderSetupData[index].ReaderFeatureLevel == 3) && (ReaderOptions[index].ReaderOptFeatures.MonetaryFormat32bitEnabled || ReaderOptions[index].ReaderOptFeatures.MultiCurrEnabled))
				{
					MDB_Byte rlimdata[5];
					memcpy(&rlimdata, &TMP[i], 10);
					ProcessReaderRevalueLimit(index,rlimdata);
					i += 4;
					
				} else
				{
					MDB_Byte rlimdata[3];
					memcpy(&rlimdata, &TMP[i], 6);
					ProcessReaderRevalueLimit(index,rlimdata);
					i += 2;
				}
			}
			break;
			case 0x11: // TIME DATE REQUEST
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*DTR", index + 1);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
			//TODO:The VMC will follow with the EXPANSION-WRITE
			//TIME/DATE FILE to the card reader. Refer to paragraph 7.4.19.
			break;
			case 0x12: // DATA ENTRY REQUEST
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*DER*%d*%d", index + 1, TMP[i + 1].data >> 7, TMP[i + 1].data & 0x7f);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
			i++;
			break;
			case 0x13: // DATA ENTRY CANCEL
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*DECNCL", index + 1);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
			//The user has pushed the reader�s RETURN button before completing the
			//DATA ENTRY. The VMC should terminate all DATA ENTRY activity in
			//progress.
			break;
			
			default:
			{
				XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*RESP???", index + 1);
				EXT_UART_Transmit_S((char*)tmpstr);
				EXT_CRLF();
			}
			break;
			
		}
	}
}

void ReaderDataEntryResponse(uint8_t index, uint8_t Keys[8])
{
	uint8_t cmd[11];
	//uint8_t addr = (index) ? 0x60 : 0x10;
	if (!index)
	{
		cmd[0] = 0x14;
	} else
	{
		cmd[0] = 0x64;
	}
	cmd[1] = 0x03;
	cmd[2] = Keys[0];
	cmd[3] = Keys[1];
	cmd[4] = Keys[2];
	cmd[5] = Keys[3];
	cmd[6] = Keys[4];
	cmd[7] = Keys[5];
	cmd[8] = Keys[6];
	cmd[9] = Keys[7];
	cmd[10] = (cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4] + cmd[5] + cmd[6] + cmd[7] + cmd[8] + cmd[9]) & 0xff;
	MDB_Send(cmd, 11);
	ReaderProcessResponse(index, "DERESP", NULL);
}

// 7.4.5 VEND - Request
// 
//
void ReaderVendRequest(uint8_t index, double price, uint16_t itemnumber)
{
	// b'DIAG*RVR5.2:4DIAG:MDBSEND:130000000208000421\r\n' - not working
	// b'DIAG*RVR5.2:4DIAG:MDBSEND:130000000208000421\r\n'
	// b'DIAG*RVR5.2:4DIAG:MDBSEND:13000000020800000000000001000000001e\r\n'

	const uint8_t itemcount = 1;
	const double optprice = 0;
	uint32_t tmpprice = round((price * pow(10, ReaderSetupData[index].DecimalPlaces)) * pow(10, ReaderSetupData[index].DecimalPlaces)) / (ReaderSetupData[index].ScalingFactor * pow(10, ReaderSetupData[index].DecimalPlaces));
	uint32_t tmpoptprice = round((optprice * pow(10, ReaderSetupData[index].DecimalPlaces)) * pow(10, ReaderSetupData[index].DecimalPlaces)) / (ReaderSetupData[index].ScalingFactor * pow(10, ReaderSetupData[index].DecimalPlaces));
	if (ReaderOptions[index].ReaderOptFeatures.MonetaryFormat32bitEnabled || ReaderOptions[index].ReaderOptFeatures.MultiCurrEnabled)
	{
		uint8_t cmd[18];
		cmd[0] = (index) ? 0x63 : 0x13;
		cmd[1] = 0x00;
		cmd[2] = (tmpprice >> 24) & 0xff;
		cmd[3] = (tmpprice >> 16) & 0xff;
		cmd[4] = (tmpprice >> 8) & 0xff;
		cmd[5] = (tmpprice >> 0 ) & 0xff; // Y5
		cmd[6] = (itemnumber >> 8) & 0xff;
		cmd[7] = (itemnumber >> 8) & 0xff; // Y7
		cmd[8] = 0; // Bytes intentionally skipped/excluded - can be set to 00h
		cmd[9] = 0; // Bytes intentionally skipped/excluded - can be set to 00h
		cmd[10] = 0; // Bytes intentionally skipped/excluded - can be set to 00h
		cmd[11] = 0; // Bytes intentionally skipped/excluded - can be set to 00h
		cmd[12] = itemcount & 0xff;
		
		
		cmd[13] = (tmpoptprice >> 24) & 0xff;
		cmd[14] = (tmpoptprice >> 16) & 0xff;
		cmd[15] = (tmpoptprice >> 8) & 0xff;
		cmd[16] = (tmpoptprice >> 0 ) & 0xff; // Y5
		cmd[17] = mdb_cmd_sum(cmd, 16);
		MDB_Send(cmd, 18);
	} else
	{
		uint8_t cmd[7];
		cmd[0] = (index) ? 0x63 : 0x13;
		cmd[1] = 0x00;
		cmd[2] = (tmpprice >> 8) & 0xff;
		cmd[3] = tmpprice & 0xff;
		cmd[4] = (itemnumber >> 8) & 0xff;
		cmd[5] = itemnumber & 0xff;
		cmd[6] = (cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4] + cmd[5]) & 0xff;
		MDB_Send(cmd, 7);
	}
	ReaderProcessResponse(index, "VENDREQ", NULL);
}

void ReaderVendCancel(uint8_t index)
{
	uint8_t cmd[3];
	cmd[0] = (index) ? 0x63 : 0x13;
	cmd[1] = 0x01;
	cmd[2] = (cmd[0] + cmd[1]) & 0xff;
	MDB_Send(cmd, 3);
	ReaderProcessResponse(index, "VENDCANCEL", NULL);
	//while (!MDBReceiveComplete){
		//MDB_read();
	//}
	//if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	//{
		//if (MDB_BUFFER[0].data == 0x06)
		//{
			//MDB_ACK();
			//sprintf(tmpstr,"CD%d*VENDCANCEL*OK\r\n", index + 1);
			//EXT_UART_Transmit_S(tmpstr);
			//return;
		//}
	//} 
	//sprintf(tmpstr,"CD%d*VENDCANCEL*", index + 1);
	//EXT_UART_Transmit_S(tmpstr);
	//EXT_UART_FAIL();
}

//
// 7.4.7 VEND - Success
//
void ReaderVendSuccess(uint8_t index, uint16_t itemnumber)
{
	uint8_t tmpstr[32];
	uint8_t cmd[5];
	cmd[0] = (index) ? 0x63 : 0x13;
	cmd[1] = 0x02;
	cmd[2] = (itemnumber >> 8) & 0xff;
	cmd[3] = itemnumber & 0xff;
	cmd[4] = (cmd[0] + cmd[1] + cmd[2] + cmd[3]) & 0xff;
	MDB_Send(cmd, 5);
	while (!MDBReceiveComplete){
		MDB_read();
	}
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*VENDSUCCESS*OK\r\n", index + 1);
			EXT_UART_Transmit_S((char*)tmpstr);
	} else
	{
		XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*VENDSUCCESS*", index + 1);
		EXT_UART_Transmit_S((char*)tmpstr);
		EXT_UART_FAIL();
	}
}

//
// 7.4.8 VEND - Failure
// 
void ReaderVendFailure(uint8_t index)
{
	//uint8_t tmpstr[32];
	//uint8_t addr = (index) ? 0x60 : 0x10;
	uint8_t cmd[3];
	if (!index)
	{
		cmd[0] = 0x13;
	} else
	{
		cmd[0] = 0x63;
	}
	cmd[1] = 0x03;
	cmd[2] = (cmd[0] + cmd[1]) & 0xff;
	MDB_Send(cmd, 3);
	ReaderProcessResponse(index, "VENDFAIL", NULL);
}

// 7.4.9 SESSION COMPLETE
//
//
void ReaderSessionComplete(uint8_t index)
{
	//uint8_t tmpstr[32];
	//uint8_t addr = (index) ? 0x60 : 0x10;
	uint8_t cmd[3];
	if (!index)
	{
		cmd[0] = 0x13;
	} else
	{
		cmd[0] = 0x63;
	}
	cmd[1] = 0x04;
	cmd[2] = (cmd[0] + cmd[1]) & 0xff;
	MDB_Send(cmd, 3);
	ReaderProcessResponse(index, "SCOMPL", NULL);
}

//
// 7.4.10 CASH SALE
// 
void ReaderCashSale(uint8_t index, double price, uint16_t itemnumber)
{
	uint32_t tmpprice = round((price * pow(10, ReaderSetupData[index].DecimalPlaces)) * 100) / (ReaderSetupData[index].ScalingFactor * 100);
	//uint8_t addr = (index) ? 0x60 : 0x10;
	
	
		if (1) {
			char tmpstr[32];
			sprintf((char*)tmpstr,"WMDIAG*:%d:%d", ReaderSetupData[index].DecimalPlaces, ReaderSetupData[index].ScalingFactor);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_CRLF();
		}

	
	uint8_t cmd[7];
	if (!index)
	{
		cmd[0] = 0x13;
	} else
	{
		cmd[0] = 0x63;
	}
	cmd[1] = 0x05;
	cmd[2] = (tmpprice >> 8) & 0xff;
	cmd[3] = (tmpprice >> 0) & 0xff;
	cmd[4] = (itemnumber >> 8) & 0xff;
	cmd[5] = itemnumber & 0xff;
	cmd[6] = (cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4] + cmd[5]) & 0xff;
	MDB_Send(cmd, 7);
	ReaderProcessResponse(index, "CSHSALE", NULL);
}

void ReaderCashSaleExp(uint8_t index, double price, uint16_t itemnumber, uint8_t currency[2])
{
	uint32_t tmpprice = round((price * pow(10, ReaderSetupData[index].DecimalPlaces)) * 100) / (ReaderSetupData[index].ScalingFactor * 100);
	//uint8_t addr = (index) ? 0x60 : 0x10;
	uint8_t cmd[11];
	if (!index)
	{
		cmd[0] = 0x13;
	} else
	{
		cmd[0] = 0x63;
	}
	cmd[1] = 0x05;
	cmd[2] = (tmpprice >> 24) & 0xff;
	cmd[3] = (tmpprice >> 16) & 0xff;
	cmd[4] = (tmpprice >> 8) & 0xff;
	cmd[5] = tmpprice & 0xff;
	cmd[6] = (itemnumber >> 8) & 0xff;
	cmd[7] = itemnumber & 0xff;
	cmd[8] = currency[0];
	cmd[9] = currency[1];
	cmd[10] = (cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4] + cmd[5] + cmd[6] + cmd[7] + cmd[8] + cmd[9]) & 0xff;
	MDB_Send(cmd, 11);
	ReaderProcessResponse(index, "CSHSALE", NULL);
}

//
// 06H - Negative Vend Request
// 7.4.11 Negative Vend Request 
//
void ReaderNegativeVend(uint8_t index, double price, uint16_t itemnumber)
{
	uint32_t tmpprice = round((price * pow(10, ReaderSetupData[index].DecimalPlaces)) * 100) / (ReaderSetupData[index].ScalingFactor * 100);
//	uint8_t addr = (index) ? 0x60 : 0x10;
	uint8_t cmd[7];
	if (!index)
	{
		cmd[0] = 0x13;
	} else
	{
		cmd[0] = 0x63;
	}
	cmd[1] = 0x06;
	cmd[2] = (tmpprice >> 8) & 0xff;
	cmd[3] = tmpprice & 0xff;
	cmd[4] = (itemnumber >> 8) & 0xff;
	cmd[5] = itemnumber & 0xff;
	cmd[6] = (cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4] + cmd[5]) & 0xff;
	MDB_Send(cmd, 7);
	ReaderProcessResponse(index, "NVEND", NULL);
}

// 
// 06H - Negative Vend Request
// 7.4.11 Negative Vend Request (Level 03 (EXPANDED CURRENCY MODE) Readers
//
void ReaderNegativeVendExp(uint8_t index, double price, uint16_t itemnumber)
{
	uint32_t tmpprice = round((price * pow(10, ReaderSetupData[index].DecimalPlaces)) * 100) / (ReaderSetupData[index].ScalingFactor * 100);
	//uint8_t addr = (index) ? 0x60 : 0x10;
	uint8_t cmd[11];
	if (!index)
	{
		cmd[0] = 0x13; // 19
	} else
	{
		cmd[0] = 0x63; // 99
	}
	cmd[1] = 0x06;

	cmd[2] = (tmpprice >> 24) & 0xff;
	cmd[3] = (tmpprice >> 16) & 0xff;
	cmd[4] = (tmpprice >> 8) & 0xff;
	cmd[5] = tmpprice & 0xff;
	
	cmd[6] = (itemnumber >> 8) & 0xff;
	cmd[7] = itemnumber & 0xff;
	
	cmd[8] = (cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4] + cmd[5] + cmd[6] + cmd[7]) & 0xff;
	MDB_Send(cmd, 11); // WM: 11?
	ReaderProcessResponse(index, "NVEND", NULL);
}

// action:
// 0x00 - DISABLE
// 0x01 - ENABLE
// 
void ReaderEDC(uint8_t index, uint8_t action)
{
	//uint8_t addr = (index) ? 0x60 : 0x10;
	uint8_t cmd[3];
	if (!index)
	{
		cmd[0] = 0x14;
	} else
	{
		cmd[0] = 0x64;
	}
	cmd[1] = action;//0x00 = Disable; 0x01 = Enable; 0x02 = Cancel
	cmd[2] = (cmd[0] + cmd[1]) & 0xff;
	MDB_Send(cmd, 3);
	ReaderProcessResponse(index, "EDC", NULL);
}

//
// 7.4.18 REVALUE - Request (Level 02 / 03 Readers)
//
void ReaderRevalueRequest(uint8_t index, double amount)
{
	uint32_t tmppamount = round((amount * pow(10, ReaderSetupData[index].DecimalPlaces)) * 100) / (ReaderSetupData[index].ScalingFactor * 100);
	//uint8_t addr = (index) ? 0x60 : 0x10;
	uint8_t cmd[5];
	if (!index)
	{
		cmd[0] = 0x15;
	} else
	{
		cmd[0] = 0x65;
	}
	cmd[1] = 0x00;
	cmd[2] = (tmppamount >> 8) & 0xff;
	cmd[3] = tmppamount & 0xff;
	cmd[4] = (cmd[0] + cmd[1] + cmd[2] + cmd[3]) & 0xff;
	MDB_Send(cmd, 5);
	ReaderProcessResponse(index, "REVRQ", NULL);
}

//
// 7.4.18 REVALUE - Request (Level 02 / 03 Readers) Level 03 (EXPANDED CURRENCY MODE) Readers
//
void ReaderRevalueRequestExp(uint8_t index, double amount)
{
	uint32_t tmppamount = round((amount * pow(10, ReaderSetupData[index].DecimalPlaces)) * 100) / (ReaderSetupData[index].ScalingFactor * 100);
	//uint8_t addr = (index) ? 0x60 : 0x10;
	uint8_t cmd[7];
	if (!index)
	{
		cmd[0] = 0x15;
	} else
	{
		cmd[0] = 0x65;
	}
	cmd[1] = 0x00;
	cmd[2] = (tmppamount >> 24) & 0xff;
	cmd[3] = (tmppamount >> 16) & 0xff;
	cmd[4] = (tmppamount >> 8) & 0xff;
	cmd[5] = tmppamount & 0xff;
	cmd[6] = (cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4] + cmd[5]) & 0xff;
	MDB_Send(cmd, 7);
	ReaderProcessResponse(index, "REVRQ", NULL);
}

void ReaderRevalueLimitRequest(uint8_t index)
{
	//uint8_t addr = (index) ? 0x60 : 0x10;
	uint8_t cmd[3];
	if (!index)
	{
		cmd[0] = 0x15;
	} else
	{
		cmd[0] = 0x65;
	}
	cmd[1] = 0x01;
	cmd[2] = (cmd[0] + cmd[1]) & 0xff;
	MDB_Send(cmd, 3);
	ReaderProcessResponse(index, "RLIMRQ", NULL);
}

void ReaderWriteDateTime(uint8_t index, uint8_t BCDDateTimeData[10])
{
	uint8_t cmd[13];
	cmd[0] = (index) ? 0x67 : 0x17;
	cmd[1] = 0x03;
	memcpy(&cmd[2], &BCDDateTimeData, 10);
	cmd[12] = (cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4] + cmd[5] + cmd[6] + cmd[7] + cmd[8] + cmd[9] + cmd[10] + cmd[11]) & 0xff;
	MDB_Send(cmd, 13);
	ReaderProcessResponse(index, "WTD", NULL);
}

void ReaderProcessResponse(uint8_t index, const char *contextdesc, uint8_t resp[])
{
	uint8_t tmpstr[32];
	//uint8_t * buff[6];
	
	
	//XXXX_sprintf_FSTR((char*)tmpstr,"WMDIAG1:CD%d:cmp:%d:errf:%d", index + 1, MDBReceiveComplete, MDBReceiveErrorFlag);
	//EXT_UART_Transmit_S((char*)tmpstr);
	
	while (!MDBReceiveComplete){
		MDB_read();
	}
	
	//XXXX_sprintf_FSTR((char*)tmpstr,"WMDIAG2:CD%d:cmp:%d:errf:%d", index + 1, MDBReceiveComplete, MDBReceiveErrorFlag);
	//EXT_UART_Transmit_S((char*)tmpstr);

	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
			//XXXX_sprintf_FSTR((char*)tmpstr,"WMDIAG:CD%d*OK*", index + 1);
			//EXT_UART_Transmit_S((char*)tmpstr);
			
		if (MDB_BUFFER_COUNT > 1)
		{
			MDB_ACK();
			
			
			EXT_UART_Transmit_HEXDUMP_MDBBYTE("RPR", MDB_BUFFER, MDB_BUFFER_COUNT);
			
			ReaderResponse(index);
			//return;
		}
		CDLED_ON(index);
		if (MDB_BUFFER_COUNT == 1)
		{
			if (strlen(contextdesc) > 1)
			{
				XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*%s*", index + 1, contextdesc);
				EXT_UART_Transmit_S((char*)tmpstr);
				if (MDB_BUFFER[0].data == 0x00 && MDB_BUFFER[0].mode)
				{
					EXT_UART_OK();
				} else
				{
					EXT_UART_NAK();
				}
			}
		}
	} else
	{
		if (strlen(contextdesc) > 1)
		{
			XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*%s*", index + 1, contextdesc);
			EXT_UART_Transmit_S((char*)tmpstr);
			EXT_UART_FAIL();
			CDLED_OFF(index);
			
				XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*MDBReceiveComplete:%d", index + 1, MDBReceiveComplete);
				EXT_UART_Transmit_S((char*)tmpstr);
				
				XXXX_sprintf_FSTR((char*)tmpstr,"CD%d*MDBReceiveErrorFlag:%d", index + 1, MDBReceiveErrorFlag);
				EXT_UART_Transmit_S((char*)tmpstr);

		}
	}
}