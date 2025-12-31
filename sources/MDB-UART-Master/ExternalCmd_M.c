/*
 * ExternalCmd_M.c
 *
 * Created: 26.08.2019 09:47:57
 *  Author: root
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include "USART_M.h"
#include "CoinChanger_M.h"
#include "BillValidator_M.h"
#include "CoinHopper_M.h"
#include "USART_M.h"
#include "Settings_M.h"
#include <stdlib.h> 
#include "config.h"


void extcmd_process_9diagnostic(uint16_t secondlevelcmd, char tmp[][6], size_t tmpcnt) {


	for(size_t z = 0; z < tmpcnt; z++) {
		EXT_UART_Transmit(">");
		EXT_UART_Transmit(tmp[z]);
		EXT_UART_Transmit("<");
		EXT_CRLF();
	}
	

	
	switch(secondlevelcmd) {
		case 1:
		 {
				EXT_UART_Transmit_S("DIAG*PING");
				EXT_CRLF();
		 }
		 break;
		case 2:
		{
			CashlessDeviceSetup(0);
			EXT_UART_Transmit_S("WMDIAG*PRICES16");
			CashlessDeviceSetupPrices16bit(0);
			EXT_UART_Transmit_S("WMDIAG*EXPANSION");
			CashlessDeviceRequestExpansionID(0);
			EXT_UART_Transmit_S("WMDIAG*OPT");
			CashlessDeviceEnableOptFetures(0);
		
			EXT_UART_Transmit_S("DIAG*ENABLE");
			ReaderEDC(0, 0x01);
		}
		break;
		case  3:
		{
			EXT_UART_Transmit_S("DIAG*RVR");
				EXT_UART_Transmit_S(tmp[0]);
				EXT_UART_Transmit_S(":");
				EXT_UART_Transmit_S(tmp[1]);
			if (tmpcnt >= 2) {
				double price = strtod(tmp[0], NULL);
				uint16_t itemnumber = atoi(tmp[1]);
				ReaderVendRequest(0, price, itemnumber);
			}
		}
		break;
		case 4:
		{
			ReaderVendSuccess(0);
		}
		break;

		case 5: {
			ReaderSessionComplete(0);
		}
		break;
		
		case 6: {
			ReaderReset(0);
		}
		break;
		
		case 7: {
			if (tmpcnt >= 1) {
				uint16_t cmd = atoi(tmp[0]);
				ReaderEDC(0, cmd);
			}
		}
		break;
		
		case 8: {
			ReaderVendFailure(0);
		}
		break;

	}
}

void EXTCMD_PROCESS() {//receive commands from VMC
	int cnt = 0;
	uint8_t tmplen = EXT_UART_BUFFER_COUNT;
	uint8_t TMP[tmplen];
	memcpy(&TMP, &EXT_UART_BUFFER, tmplen);
	

//	EXT_UART_Transmit_HEXDUMP(TMP, tmplen);
	
	EXT_UART_BUFFER_COUNT = 0;
	EXTCMDCOMPLETE = 0;
	for (int i = 0; i < tmplen; i++)
	{
		if (TMP[i] == '*') cnt++;
	}
	char tmp[cnt][6];
	int tmpcnt = 0;
	char * p = strtok((char*)TMP, "*");
	while (p) {
		if ((tmpcnt < cnt) && (sizeof(p) <= 6)) strcpy((char*)&tmp[tmpcnt++], p);
		p = strtok(NULL, "*");
	}
	
	if (tmpcnt > 0)
	{
		uint16_t toplevelcmd = atoi((char*)&tmp[0]);
		uint16_t secondlevelcmd = atoi((char*)&tmp[1]);
		switch (toplevelcmd)
		{
			case 0:
			{
				switch (secondlevelcmd)
				{
					case 0:
					ResetAll();
					break;
					case 1:
					ResetCoinChangerOptions();
					break;
					case 2:
					ResetBVOptions();
					break;
					case 3:
					ResetCoinHoppersOptions();
					break;
				}
			}
			break;
			case 1:
			switch (secondlevelcmd)
			{
				case 1:
				MDBDeviceReset(0x08);
				break;
				case 2:
				GetCoinChangerSetupData();
				GetCoinChangerTubeStatus();
				GetCoinChangerIdentification();
				break;
				case 3:
				CoinChangerEnableAcceptCoins();
				break;
				case 4:
				CoinChangerDisableAcceptCoins();
				break;
				case 5:
				{
					if (cnt == 4)
					{
						uint8_t DispenseParams = (atoi((char*)&tmp[3]) << 4) & 0xff;//high 4 bits - quantity, max value = 15
						DispenseParams = DispenseParams | ((atoi((char*)&tmp[2]) & 0x0f) - 1);//lower 4 bits - coin type, max value = 15
						CoinChangerDispense(DispenseParams);
					}
				}
				break;
				case 6:
				if (cnt == 3)
				{
					CoinChangerAlternativePayout(atoi((char*)&tmp[2]) & 0xff);
				}
				break;
				case 7:
				//CoinChangerControlledManualFillReport();
				break;
				case 8:
				if (cnt == 5)
				{
					CoinChangerEnableCoinType(atoi((char*)&tmp[2]),atoi((char*)&tmp[3]),atoi((char*)&tmp[4]));
				}
				break;
				case 9:
				if (cnt == 5)
				{
					CoinChangerConfigFeatures(atoi((char*)&tmp[2]),atoi((char*)&tmp[3]),atoi((char*)&tmp[4]));
				}
				break;
			}
			break;
			case 2:
			switch (secondlevelcmd)
			{
				case 1:
				MDBDeviceReset(0x30);
				break;
				case 2:
				GetBillValidatorSetupData();
				break;
				case 3:
				BillValidatorEnableAcceptBills();
				break;
				case 4:
				BillValidatorDisableAcceptBills();
				break;
				case 5:
				if (cnt == 3)
				{
					BillValidatorEscrow(atoi((char*)&tmp[2]) & 0x01);
				}
				break;
				case 6:
				if (cnt == 4)
				{
					BVDispenseBills(atoi((char*)&tmp[2]) & 0xff, atoi((char*)&tmp[3]) & 0xffff);
				}
				break;
				case 7:
				if (cnt == 3)
				{
					BVDispenseValue(atoi((char*)&tmp[2]) & 0xffff);
				}
				break;
				case 8:
				if (cnt == 8)
				{
					BillValidatorEnableBillType(atoi((char*)&tmp[2]),atoi((char*)&tmp[3]),atoi((char*)&tmp[4]),atoi((char*)&tmp[5]),atoi((char*)&tmp[6]),atoi((char*)&tmp[7]));
				}
				break;
				case 9:
				if (cnt == 3)
				{
					BillValidatorConfigFeatures(atoi((char*)&tmp[2]));
				}
				break;
				case 10:
				BillValidatorCancelPayout();
				break;
			}
			break;
			case 3:
			if (cnt >= 3)
			{
				uint8_t index = (atoi((char*)&tmp[1]) == 1) ? 0 : 1;
				uint16_t thirdlevelcmd = atoi((char*)&tmp[2]);
				switch (thirdlevelcmd)
				{
					case 1:
					MDBDeviceReset((index) ? 0x73 : 0x58);
					break;
					case 2:
					GetCoinHopperSetupData(index);
					GetCoinHopperIdentification(index);
					break;
					case 6:
					if (cnt == 5)
					{
						CoinHopperDispenseCoins(index, atoi((char*)&tmp[3]) & 0xff, atoi((char*)&tmp[4]) & 0xffff);
					}
					break;
					case 7:
					if (cnt == 4)
					{
						CoinHopperDispenseValue(index, atoi((char*)&tmp[3]) & 0xffff);
					}
					break;
					case 8:
					if (cnt == 5)
					{
						CoinHopperEnableManualDispenseCoinType(index, atoi((char*)&tmp[3]) & 0xff, atoi((char*)&tmp[4]) & 0xff);
					}
					break;
				}
			}
			break;
			case 9: // WM diag
			{
				extcmd_process_9diagnostic(secondlevelcmd, &tmp[2], tmpcnt-2);
			}
			break;
			
		}
	}
}