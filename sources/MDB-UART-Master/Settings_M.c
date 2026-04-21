/*
 * Settings_M.c
 *
 * Created: 18.05.2019 10:11:12
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
#include "Cashless_M.h"
#include "BillValidator_M.h"
#include "CoinChanger_M.h"
#include "CoinHopper_M.h"
#include "Settings_M.h"
#include "MDB_M.h"

VMCData_t VMCData;
ReaderOptions_t ReaderOptions[2];
CoinChangerOptions_t CoinChangerOptions;
BillValidatorOptions_t BillValidatorOptions;
CoinHopperOptions_t CoinHopperOptions[2];

//  3 - The VMC is able to support level 02, but also supports some or all of
// 16 - 16 columns?
//  2 - 2 rows
//  1 - Full ASCII
//
VMCData_t EEMEM nv_VMCData = {3,16,2,1,"OTA","000000000123","000000000002","03"};
//ReaderOptions_t EEMEM nv_ReaderOptions[2] = {{0xffffffff,0x00000000,{0x10,0x18},{0,1,1,1,0,1}},{0xffffffff, 0x00000000,{0x10,0x18},{0,1,1,1,0,1}}}; //original
  ReaderOptions_t EEMEM nv_ReaderOptions[2] = {
		  {
			//.MaxPrice={.Value=0xffffffff}, //cashlessprice32bit maxprice union{unsigned long Value;uint8_t Bytes[4];} cashlessprice32bit;
			.MaxPrice={.Bytes={0x07,0xd0,0x00,0x00}}, //cashlessprice32bit maxprice union{unsigned long Value;uint8_t Bytes[4];} cashlessprice32bit;
			.MinPrice={.Value=0x00000000}, //minprice
			.CountryOrCurrencyCode={0x19,0x85}, //country currency code [2] = PLN
//			{.MonetaryFormat32bitEnabled=1, .MultiCurrEnabled=1, .NegVendEnabled=1, .AlwaysIdleEnabled=1} //reader opt features
		{.MonetaryFormat32bitEnabled=0, .MultiCurrEnabled=0, .NegVendEnabled=1, .AlwaysIdleEnabled=1} //reader opt features				
		   },
		   {
			.MaxPrice={.Value=0xffffffff}, 
			.MinPrice={.Value=0x00000000},
			.CountryOrCurrencyCode={0x10,0x18},
			{0,1,1,1,0,1}
			}
		};

CoinChangerOptions_t EEMEM nv_CoinChangerOptions = {0xffff,0xffff,0x07};
BillValidatorOptions_t EEMEM nv_BillValidatorOptions = {0xffff,0xffff,0x0000,0xffff,0x0000,1};
CoinHopperOptions_t EEMEM nv_CoinHopperOptions[2] = {{0xffff},{0xffff}};

static void DiagPrintVMC(void)
{
	char buf[96];
	sprintf(buf, "DIAG:VMC*FL:%d*DISP:%dx%d*DTYPE:%d*MFG:%.3s*SN:%.12s*MDL:%.12s*SW:%.2s",
		VMCData.VMC_FEATURE_LEVEL,
		VMCData.VMC_DISPLAY_COLUMNS, VMCData.VMC_DISPLAY_ROWS,
		VMCData.VMC_DISPLAY_TYPE,
		VMCData.VMCMfgCode, VMCData.VMCSerialNumber,
		VMCData.VMCModelNumber, VMCData.VMCSofwareVersion);
	EXT_UART_Transmit_S(buf);
	EXT_CRLF();
}

static void DiagPrintReaderOpts(uint8_t index)
{
	char buf[80];
	ReaderOptions_t *r = &ReaderOptions[index];
	sprintf(buf, "DIAG:CD%d*MAXP:%02x%02x%02x%02x*MINP:%02x%02x%02x%02x*CUR:%02x%02x",
		index + 1,
		r->MaxPrice.Bytes[0], r->MaxPrice.Bytes[1],
		r->MaxPrice.Bytes[2], r->MaxPrice.Bytes[3],
		r->MinPrice.Bytes[0], r->MinPrice.Bytes[1],
		r->MinPrice.Bytes[2], r->MinPrice.Bytes[3],
		r->CountryOrCurrencyCode[0], r->CountryOrCurrencyCode[1]);
	EXT_UART_Transmit_S(buf);
	sprintf(buf, "*FTL:%d*32B:%d*MCUR:%d*NVEND:%d*DENT:%d*IDLE:%d",
		r->ReaderOptFeatures.FTLEnabled,
		r->ReaderOptFeatures.MonetaryFormat32bitEnabled,
		r->ReaderOptFeatures.MultiCurrEnabled,
		r->ReaderOptFeatures.NegVendEnabled,
		r->ReaderOptFeatures.DataEntryEnabled,
		r->ReaderOptFeatures.AlwaysIdleEnabled);
	EXT_UART_Transmit_S(buf);
	EXT_CRLF();
}

static void DiagPrintCCOpts(void)
{
	char buf[48];
	sprintf(buf, "DIAG:CC*ACCEPT:%04x*DISP:%04x*EXT:%02x",
		CoinChangerOptions.EnableAcceptCoinsBits,
		CoinChangerOptions.EnableDispenseCoinsBits,
		CoinChangerOptions.EnableExtOptionsBits);
	EXT_UART_Transmit_S(buf);
	EXT_CRLF();
}

static void DiagPrintBVOpts(void)
{
	char buf[80];
	sprintf(buf, "DIAG:BV*SEC:%04x*ACCEPT:%04x*ESCROW:%04x*RECYCLE:%04x*MANDISP:%04x*RECEN:%d",
		BillValidatorOptions.BillSecurityBits,
		BillValidatorOptions.EnableAcceptBillsBits,
		BillValidatorOptions.EnableEscrowBillsBits,
		BillValidatorOptions.EnableRecycleBillsBits,
		BillValidatorOptions.EnableManualDispenseBillsBits,
		BillValidatorOptions.EnableBillRecycling);
	EXT_UART_Transmit_S(buf);
	EXT_CRLF();
}

static void DiagPrintCHOpts(uint8_t index)
{
	char buf[32];
	sprintf(buf, "DIAG:CH%d*MANDISP:%04x*EXT:%02x",
		index + 1,
		CoinHopperOptions[index].EnableManualDispenseCoinsBits,
		CoinHopperOptions[index].EnableExtOptionsBits);
	EXT_UART_Transmit_S(buf);
	EXT_CRLF();
}

void ReadVMCData()
{
	eeprom_read_block((void*)&VMCData, (const void*)&nv_VMCData, sizeof(VMCData_t));
	EXT_UART_Transmit_S("SYS*VMCSET*READ*");
	EXT_UART_OK();
	EXT_UART_Transmit_HEXDUMP("VMCDATA", &VMCData, sizeof(VMCData));
	DiagPrintVMC();
}

void ReadCashlessPrices()
{
	eeprom_read_block((void*)&ReaderOptions, (const void*)&nv_ReaderOptions, sizeof(ReaderOptions));
	EXT_UART_Transmit_S("SYS*CDSET*READ*");
	EXT_UART_OK();
	EXT_UART_Transmit_HEXDUMP("READEROPTIONS", &ReaderOptions, sizeof(ReaderOptions));
	DiagPrintReaderOpts(0);
	DiagPrintReaderOpts(1);
}

void ReadCoinChangerOptions()
{
	eeprom_read_block((void*)&CoinChangerOptions, (const void*)&nv_CoinChangerOptions, sizeof(CoinChangerOptions_t));
	DiagPrintCCOpts();
	EXT_UART_Transmit_S("SYS*CCSET*READ*");
	EXT_UART_OK();
}

void WriteCoinChangerOptions()
{
	eeprom_write_block((void*)&CoinChangerOptions, (void*)&nv_CoinChangerOptions, sizeof(CoinChangerOptions_t));
	EXT_UART_Transmit_S("SYS*CCSET*SAVE*");
	EXT_UART_OK();
}

void ResetCoinChangerOptions()
{
	uint8_t tmp[5] = {0xff,0xff,0xff,0xff,0x07};
	eeprom_write_block((void*)&tmp, (void*)&nv_CoinChangerOptions, sizeof(CoinChangerOptions_t));
	eeprom_read_block((void*)&CoinChangerOptions, (const void*)&nv_CoinChangerOptions, sizeof(CoinChangerOptions_t));
	EXT_UART_Transmit_S("SYS*CCSET*RESET*");
	EXT_UART_OK();
}

void ReadBVOptions()
{
	eeprom_read_block((void*)&BillValidatorOptions, (const void*)&nv_BillValidatorOptions, sizeof(BillValidatorOptions_t));
	DiagPrintBVOpts();
	EXT_UART_Transmit_S("SYS*BVSET*READ*");
	EXT_UART_OK();
}

void WriteBVOptions()
{
	eeprom_write_block((void*)&BillValidatorOptions, (void*)&nv_BillValidatorOptions, sizeof(BillValidatorOptions_t));
	EXT_UART_Transmit_S("SYS*BVSET*SAVE*");
	EXT_UART_OK();
}

void ResetBVOptions()
{
	uint8_t tmp[11] = {0xff,0xff, 0xff,0xff, 0x00,0x00, 0xff,0xff, 0x00,0x00, 1};
	eeprom_write_block((void*)&tmp, (void*)&nv_BillValidatorOptions, sizeof(BillValidatorOptions_t));
	eeprom_read_block((void*)&BillValidatorOptions, (void*)&nv_BillValidatorOptions, 11);
	EXT_UART_Transmit_S("SYS*BVSET*RESET*");
	EXT_UART_OK();
}

void ReadCoinHoppersOptions()
{
	eeprom_read_block((void*)&CoinHopperOptions, (const void*)&nv_CoinHopperOptions, sizeof(CoinHopperOptions));
	DiagPrintCHOpts(0);
	DiagPrintCHOpts(1);
	EXT_UART_Transmit_S("SYS*CHSET*READ*");
	EXT_UART_OK();
}

void WriteCoinHoppersOptions()
{
	eeprom_write_block((void*)&CoinHopperOptions, (void*)&nv_CoinHopperOptions, sizeof(CoinHopperOptions));
	EXT_UART_Transmit_S("SYS*CHSET*SAVE*");
	EXT_UART_OK();
}

void ResetCoinHoppersOptions()
{
	uint8_t tmp[4] = {0xff,0xff,0xff,0xff};
	eeprom_write_block((void*)&tmp, (void*)&nv_CoinHopperOptions, 4);
	eeprom_read_block((void*)&CoinHopperOptions, (const void*)&nv_CoinHopperOptions, sizeof(CoinHopperOptions));
	EXT_UART_Transmit_S("SYS*CHSET*RESET*");
	EXT_UART_OK();
}
