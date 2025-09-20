/*
 * MDB_M.c
 *
 * Created: 18.05.2019 09:56:50
 *  Author: root
 */ 
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include "USART_M.h"
#include "CoinChanger_M.h"
#include "CoinHopper_M.h"
#include "BillValidator_M.h"
#include "Cashless_M.h"
#include "Settings_M.h"
#include "MDB_M.h"
#include "config.h"
#include "config.h"
#include <stdlib.h>
#include <avr/flash.h>

void MDBDebug()
{
	unsigned char * buff[32];
	sprintf_FSTR((char*)buff, "Bytes count: %d, content: ", MDB_BUFFER_COUNT);
	EXT_UART_Transmit_S((char*)buff);
	for (int a = 0; a < MDB_BUFFER_COUNT - 1; a++)
	{
		sprintf_FSTR((char*)buff, "%02x ", MDB_BUFFER[a].data);
		EXT_UART_Transmit_S((char*)buff);
	}
	sprintf_FSTR((char*)buff, "%02x\r\n", MDB_BUFFER[MDB_BUFFER_COUNT - 1].data);
	EXT_UART_Transmit_S((char*)buff);
}

void ProcessMDBResponse(uint8_t addr){
	MDBReceiveErrorFlag = 0;
	MDBReceiveComplete = 0;
	MDB_BUFFER_COUNT = 0;
	while (!MDBReceiveComplete){
		MDB_read();
	}
	if ((MDBReceiveComplete) && (!MDBReceiveErrorFlag))
	{
		if (MDB_BUFFER_COUNT > 1){
			MDB_ACK();
			switch (addr)
			{
				case 0x08:
				CoinChangerPollResponse();
				break;
				case 0x30:
				BillValidatorPollResponse();
				break;
				case 0x58:
				CoinHopperPollResponse(0);
				break;
				case 0x70:
				CoinHopperPollResponse(1);
				break;
			}
			} else{
			if (MDB_BUFFER_COUNT == 1){
				//just *ACK* received from peripheral device, no confirmation needed
				//MDBDebug();
				if (MDB_BUFFER[0].data == 0x00 && MDB_BUFFER[0].mode)
				{
					switch (addr)
					{
						case 0x08:
						if (CoinChangerDevice.Status == 2)
						{
							CoinChangerDevice.Status = 1;
							EXT_UART_Transmit_S("CC*DISP*FIN\r\n");
							GetCoinChangerTubeStatus();
						}
						break;
						case 0x58:
						if (CoinHopperDevice[0].Status == 2)
						{
							CoinHopperDevice[0].Status = 1;
							EXT_UART_Transmit_S("CH1*DISP*FIN\r\n");
							GetCoinHopperDispenserStatus(0);
						}
						break;
						case 0x73:
						if (CoinHopperDevice[1].Status == 2)
						{
							CoinHopperDevice[1].Status = 1;
							EXT_UART_Transmit_S("CH2*DISP*FIN\r\n");
							GetCoinHopperDispenserStatus(1);
						}
						break;
						case 0x30:
						if (BillValidatorDevice.Status == 2)
						{
							BillValidatorDevice.Status = 1;
						}
						break;
					}
				}
			}
		}
	} else
	{
		switch (addr)
		{
			case 0x08:
			if (CoinChangerDevice.OfflinePollsCount > 0) CoinChangerDevice.OfflinePollsCount--;
			break;
			case 0x30:
			if (BillValidatorDevice.OfflinePollsCount > 0) BillValidatorDevice.OfflinePollsCount--;
			break;
			case 0x58:
			if (CashlessDevice[0].OfflinePollsCount > 0) CashlessDevice[0].OfflinePollsCount--;
			break;
			case 0x70:
			if (CashlessDevice[1].OfflinePollsCount > 0) CashlessDevice[1].OfflinePollsCount--;
			break;
		}
	}
}

void PollDevice(uint8_t address)
{
	uint8_t tmp2[2] = {address, address};
	MDB_Send(tmp2, 2);
	ProcessMDBResponse(address & 0xf8);
}

void PollReader(uint8_t index)
{
	uint8_t addr = (index == 1) ? 0x62 : 0x12;

	MDBReceiveErrorFlag = 0;
	MDBReceiveComplete = 0;
	MDB_BUFFER_COUNT = 0;

	/* --- send first 9-bit word with TXDATAH = 1 --- */
	while (!(EXT_STATUS & USART_DREIF_bm)) {}  // wait until TX buffer empty
	EXT_TXDATAH = 0x01;                        // set 9th bit = 1
	EXT_TXDATAL = addr;

	/* --- send second 9-bit word with TXDATAH = 0 --- */
	while (!(EXT_STATUS & USART_DREIF_bm)) {}
	EXT_TXDATAH = 0x00;                        // 9th bit = 0
	EXT_TXDATAL = addr;

	ReaderProcessResponse(index, (uint8_t*)"");
}

void DebugMDBMessage()
{
	uint8_t * buff[20];
	sprintf_FSTR((char*)buff, "Bytes: %d\r\nHEX:", MDB_BUFFER_COUNT);
	EXT_UART_Transmit_S((char*)buff);
	for (int a = 0; a < MDB_BUFFER_COUNT - 1; a++){
	sprintf_FSTR((char*)buff, " %02x", MDB_BUFFER[a].data);
	EXT_UART_Transmit_S((char*)buff);
	}
	sprintf_FSTR((char*)buff, " %02x", MDB_BUFFER[MDB_BUFFER_COUNT - 1].data);
	EXT_UART_Transmit_S((char*)buff);
	EXT_CRLF();
}

void MDBDeviceReset(uint8_t DevAddress)
{
	uint8_t cmd[2] = {DevAddress, DevAddress};
	MDB_Send(cmd, 2);
	ProcessMDBResponse(DevAddress);
}


void ResetAll()
{
	uint8_t RESET_ADDRESS[10] = {0x0B, 0x33, 0x42, 0x4A, 0x52, 0x5B, 0x73};
	for (int q = 0; q < 7; q++)
	{
		uint8_t cmd[2] = { (RESET_ADDRESS[q] & 0xf8), RESET_ADDRESS[q] & 0xf8 };
		MDB_Send(cmd, 2);
		ProcessMDBResponse(RESET_ADDRESS[q] & 0xf8);
	}
	//ReaderReset(0);
	//ReaderReset(1);
}