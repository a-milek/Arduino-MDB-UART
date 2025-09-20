/*
 * LEDControl_M.c
 *
 * ATmega4808 version
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
#include "Settings_M.h"
#include "LEDControl_M.h"

const char * str_devonline = "SYS*DEVONLINE*";
const char * str_devlost   = "SYS*DEVLOST*";

void CCLED_ON()
{
    if (!(PORTD.OUT & PIN6_bm))
    {
        PORTD.OUTSET = PIN6_bm;
        EXT_UART_Transmit_S((char*)str_devonline);
        EXT_UART_Transmit_S("CC");
        EXT_CRLF();
    }
}

void CCLED_OFF()
{
    if (PORTD.OUT & PIN6_bm)
    {
        PORTD.OUTCLR = PIN6_bm;
        EXT_UART_Transmit_S((char*)str_devlost);
        EXT_UART_Transmit_S("CC");
        EXT_CRLF();
    }
}

void BVLED_ON()
{
    if (!(PORTC.OUT & PIN5_bm))
    {
        PORTC.OUTSET = PIN5_bm;
        EXT_UART_Transmit_S((char*)str_devonline);
        EXT_UART_Transmit_S("BV");
        EXT_CRLF();
    }
}

void BVLED_OFF()
{
    if (PORTC.OUT & PIN5_bm)
    {
        PORTC.OUTCLR = PIN5_bm;
        EXT_UART_Transmit_S((char*)str_devlost);
        EXT_UART_Transmit_S("BV");
        EXT_CRLF();
    }
}

void CHLED_ON(uint8_t index)
{
    if (index)
    {
        if (!(PORTD.OUT & PIN5_bm))
        {
            PORTD.OUTSET = PIN5_bm;
            EXT_UART_Transmit_S((char*)str_devonline);
            EXT_UART_Transmit_S("CH2");
            EXT_CRLF();
        }
    }
    else
    {
        if (!(PORTD.OUT & PIN4_bm))
        {
            PORTD.OUTSET = PIN4_bm;
            EXT_UART_Transmit_S((char*)str_devonline);
            EXT_UART_Transmit_S("CH1");
            EXT_CRLF();
        }
    }
}

void CHLED_OFF(uint8_t index)
{
    if (index)
    {
        if (PORTD.OUT & PIN5_bm)
        {
            PORTD.OUTCLR = PIN5_bm;
            EXT_UART_Transmit_S((char*)str_devlost);
            EXT_UART_Transmit_S("CH2");
            EXT_CRLF();
        }
    }
    else
    {
        if (PORTD.OUT & PIN4_bm)
        {
            PORTD.OUTCLR = PIN4_bm;
            EXT_UART_Transmit_S((char*)str_devlost);
            EXT_UART_Transmit_S("CH1");
            EXT_CRLF();
        }
    }
}

void CDLED_ON(uint8_t index)
{
    if (index) PORTC.OUTSET = PIN5_bm;
    else       PORTC.OUTSET = PIN6_bm;
}

void CDLED_OFF(uint8_t index)
{
    if (index) PORTC.OUTCLR = PIN5_bm;
    else       PORTC.OUTCLR = PIN6_bm;
}

void USDLED_ON(uint8_t index)
{
    if (index == 0) PORTC.OUTSET = PIN4_bm;
    else if (index == 1) PORTC.OUTSET = PIN2_bm;
    else if (index == 2) PORTC.OUTSET = PIN3_bm;
}

void USDLED_OFF(uint8_t index)
{
    if (index == 0) PORTC.OUTCLR = PIN4_bm;
    else if (index == 1) PORTC.OUTCLR = PIN2_bm;
    else if (index == 2) PORTC.OUTCLR = PIN3_bm;
}


void DIAGLED_FLASH(uint8_t pulses) {
	for(int8_t k = 0; k < pulses; k++) {
		PORTC.OUTSET = PIN2_bm;
		PORTC.OUTCLR = PIN2_bm;
	}
}

void LED_SETUP(void) {
	// so far only one
	PORTC.DIRSET = PIN2_bm;
}