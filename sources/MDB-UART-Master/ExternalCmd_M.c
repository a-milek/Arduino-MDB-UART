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
#include "Cashless_M.h"
#include "Settings_M.h"
#include <stdlib.h>
#include "config.h"

/* --- Safe buffer snapshot: copies volatile buffer under cli/sei --- */
static void extcmd_snapshot(char *buf, size_t bufsz)
{
	cli();
	uint8_t len = EXT_UART_BUFFER_COUNT;
	if (len >= bufsz) len = bufsz - 1;
	memcpy(buf, (const void *)EXT_UART_BUFFER, len);
	EXT_UART_BUFFER_COUNT = 0;
	EXTCMDCOMPLETE = 0;
	sei();
	buf[len] = '\0';
}

/* --- Field-peeling helpers --- */

// Parse leading decimal integer from *s, advance past next '*'.
// Returns dflt if *s is empty or NULL.
static uint16_t extcmd_next_u16(const char **s, uint16_t dflt)
{
	if (*s == NULL || **s == '\0') return dflt;
	uint16_t val = (uint16_t)atoi(*s);
	const char *sep = strchr(*s, '*');
	*s = sep ? sep + 1 : *s + strlen(*s);
	return val;
}

// Parse leading double from *s, advance past next '*'.
static double extcmd_next_double(const char **s, double dflt)
{
	if (*s == NULL || **s == '\0') return dflt;
	double val = strtod(*s, NULL);
	const char *sep = strchr(*s, '*');
	*s = sep ? sep + 1 : *s + strlen(*s);
	return val;
}

// Count remaining '*'-delimited fields. "" → 0, "x" → 1, "x*y" → 2.
static uint8_t extcmd_argc(const char *s)
{
	if (s == NULL || *s == '\0') return 0;
	uint8_t n = 1;
	while (*s) {
		if (*s == '*') n++;
		s++;
	}
	return n;
}

// Get pointer to current field value without advancing (for string access)
static const char *extcmd_field_str(const char *s)
{
	return (s && *s) ? s : "";
}

/* --- Device dispatch functions --- */

static void extcmd_process_0reset(const char *args)
{
	uint16_t sub = extcmd_next_u16(&args, 0xFF);
	switch (sub) {
		case 0: ResetAll(); break;
		case 1: ResetCoinChangerOptions(); break;
		case 2: ResetBVOptions(); break;
		case 3: ResetCoinHoppersOptions(); break;
	}
}

static void extcmd_process_1coinchanger(const char *args)
{
	uint16_t sub = extcmd_next_u16(&args, 0xFF);

	switch (sub) {
		case 1:
			MDBDeviceReset(0x08);
			break;
		case 2:
			GetCoinChangerSetupData();
			GetCoinChangerTubeStatus();
			GetCoinChangerIdentification();
			break;
		case 3: {
			// "1*3*+" / "1*3*65535*+" / "1*3*65535*65535*+"
			uint16_t accept = extcmd_next_u16(&args, 0xFFFF);
			uint16_t dispense = extcmd_next_u16(&args, 0xFFFF);
			CoinChangerEnableAcceptCoins(accept, dispense);
			break;
		}
		case 4:
			CoinChangerDisableAcceptCoins();
			break;
		case 5:
			if (extcmd_argc(args) >= 2) {
				uint8_t cointype = extcmd_next_u16(&args, 0) & 0x0f;
				uint8_t quantity = extcmd_next_u16(&args, 0) & 0x0f;
				uint8_t params = (quantity << 4) | (cointype - 1);
				CoinChangerDispense(params);
			}
			break;
		case 6:
			if (extcmd_argc(args) >= 1) {
				CoinChangerAlternativePayout(extcmd_next_u16(&args, 0) & 0xff);
			}
			break;
		case 7:
			break;
		case 8:
			if (extcmd_argc(args) >= 3) {
				uint8_t a = extcmd_next_u16(&args, 0) & 0xff;
				uint8_t b = extcmd_next_u16(&args, 0) & 0xff;
				uint8_t c = extcmd_next_u16(&args, 0) & 0xff;
				CoinChangerEnableCoinType(a, b, c);
			}
			break;
		case 9:
			if (extcmd_argc(args) >= 3) {
				uint8_t a = extcmd_next_u16(&args, 0) & 0xff;
				uint8_t b = extcmd_next_u16(&args, 0) & 0xff;
				uint8_t c = extcmd_next_u16(&args, 0) & 0xff;
				CoinChangerConfigFeatures(a, b, c);
			}
			break;
		case 0x0a:
			EXT_UART_Transmit_S("DIAG:9\r\n");
			GetCoinChangerTubeStatus();
			EXT_UART_Transmit_S("DIAG:10\r\n");
			break;
	}
}

static void extcmd_process_2billvalidator(const char *args)
{
	uint16_t sub = extcmd_next_u16(&args, 0xFF);

	switch (sub) {
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
			if (extcmd_argc(args) >= 1) {
				BillValidatorEscrow(extcmd_next_u16(&args, 0) & 0x01);
			}
			break;
		case 6:
			if (extcmd_argc(args) >= 2) {
				uint8_t count = extcmd_next_u16(&args, 0) & 0xff;
				uint16_t value = extcmd_next_u16(&args, 0);
				BVDispenseBills(count, value);
			}
			break;
		case 7:
			if (extcmd_argc(args) >= 1) {
				BVDispenseValue(extcmd_next_u16(&args, 0));
			}
			break;
		case 8:
			if (extcmd_argc(args) >= 6) {
				uint8_t a = extcmd_next_u16(&args, 0) & 0xff;
				uint8_t b = extcmd_next_u16(&args, 0) & 0xff;
				uint8_t c = extcmd_next_u16(&args, 0) & 0xff;
				uint8_t d = extcmd_next_u16(&args, 0) & 0xff;
				uint8_t e = extcmd_next_u16(&args, 0) & 0xff;
				uint8_t f = extcmd_next_u16(&args, 0) & 0xff;
				BillValidatorEnableBillType(a, b, c, d, e, f);
			}
			break;
		case 9:
			if (extcmd_argc(args) >= 1) {
				BillValidatorConfigFeatures(extcmd_next_u16(&args, 0) & 0xff);
			}
			break;
		case 10:
			BillValidatorCancelPayout();
			break;
	}
}

static void extcmd_process_3coinhopper(const char *args)
{
	if (extcmd_argc(args) < 2) return;

	uint8_t index = (extcmd_next_u16(&args, 1) == 1) ? 0 : 1;
	uint16_t sub = extcmd_next_u16(&args, 0xFF);

	switch (sub) {
		case 1:
			MDBDeviceReset(index ? 0x73 : 0x58);
			break;
		case 2:
			GetCoinHopperSetupData(index);
			GetCoinHopperIdentification(index);
			break;
		case 6:
			if (extcmd_argc(args) >= 2) {
				uint8_t cointype = extcmd_next_u16(&args, 0) & 0xff;
				uint16_t count = extcmd_next_u16(&args, 0);
				CoinHopperDispenseCoins(index, cointype, count);
			}
			break;
		case 7:
			if (extcmd_argc(args) >= 1) {
				CoinHopperDispenseValue(index, extcmd_next_u16(&args, 0));
			}
			break;
		case 8:
			if (extcmd_argc(args) >= 2) {
				uint8_t a = extcmd_next_u16(&args, 0) & 0xff;
				uint8_t b = extcmd_next_u16(&args, 0) & 0xff;
				CoinHopperEnableManualDispenseCoinType(index, a, b);
			}
			break;
	}
}

static void extcmd_process_9diagnostic(const char *args)
{
	uint16_t sub = extcmd_next_u16(&args, 0xFF);

	switch (sub) {
		case 1:
			EXT_UART_Transmit_S("DIAG*PING");
			EXT_CRLF();
			break;
		case 2:
			// ref 7.4.1 Reset and Initialising
			CashlessDeviceSetup(0);
			EXT_UART_Transmit_S("DIAG:PRICES16\r\n");
			CashlessDeviceSetupPrices16bit(0);
			EXT_UART_Transmit_S("DIAG:EXPANSION\r\n");
			CashlessDeviceRequestExpansionID(0);
			EXT_UART_Transmit_S("DIAG:OPT\r\n");
			CashlessDeviceEnableOptFetures(0);
			CashlessDeviceSetupPrices32bit(0);
			EXT_UART_Transmit_S("DIAG:ENABLE\r\n");
			ReaderEDC(0, 0x01);
			break;
		case 3:
			if (extcmd_argc(args) >= 2) {
				const char *price_str = extcmd_field_str(args);
				double price = extcmd_next_double(&args, 0.0);
				const char *item_str = extcmd_field_str(args);
				uint16_t itemnumber = extcmd_next_u16(&args, 0);
				EXT_UART_Transmit_S("DIAG*RVR");
				EXT_UART_Transmit_S(price_str);
				EXT_UART_Transmit_S(":");
				EXT_UART_Transmit_S(item_str);
				EXT_CRLF();
				ReaderVendRequest(0, price, itemnumber);
			}
			break;
		case 4:
			if (extcmd_argc(args) >= 1) {
				ReaderVendSuccess(0, extcmd_next_u16(&args, 0));
			}
			break;
		case 5:
			ReaderSessionComplete(0);
			break;
		case 6:
			ReaderReset(0);
			break;
		case 7:
			if (extcmd_argc(args) >= 1) {
				ReaderEDC(0, extcmd_next_u16(&args, 0));
			}
			break;
		case 8:
			ReaderVendFailure(0);
			break;
		case 9:
			if (extcmd_argc(args) >= 2) {
				double price = extcmd_next_double(&args, 0.0);
				uint16_t itemnumber = extcmd_next_u16(&args, 0);
				ReaderCashSale(0, price, itemnumber);
			}
			break;
		case 10:
			ReaderVendCancel(0);
			break;
	}
}

static void extcmd_process_10system(const char *args)
{
	uint16_t sub = extcmd_next_u16(&args, 0xFF);

	switch (sub) {
		case 1:
			EXT_UART_Transmit_S("SYS*PING*OK");
			EXT_CRLF();
			break;
		case 99:
			EXT_UART_Transmit_S("SYS*RESET*OK");
			EXT_CRLF();
			delay_1ms(10);
			CPU_CCP = CCP_IOREG_gc;
			RSTCTRL.SWRR = (1 << RSTCTRL_SWRE_bp);
			while(1) {};
			break;
	}
}

/* --- Main dispatcher --- */

void EXTCMD_PROCESS(void)
{
	char buf[33];
	extcmd_snapshot(buf, sizeof(buf));

	const char *s = buf;
	if (*s == '\0') return;

	uint16_t top = extcmd_next_u16(&s, 0xFF);
	switch (top) {
		case 0:  extcmd_process_0reset(s);          break;
		case 1:  extcmd_process_1coinchanger(s);    break;
		case 2:  extcmd_process_2billvalidator(s);  break;
		case 3:  extcmd_process_3coinhopper(s);     break;
		case 9:  extcmd_process_9diagnostic(s);     break;
		case 10: extcmd_process_10system(s);        break;
	}
}
