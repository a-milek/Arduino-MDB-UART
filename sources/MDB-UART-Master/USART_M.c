/*
 * USART_M.c
 *
 * ATmega4808-adapted USART helper for MDB + EXT
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
#include "USART_M_conf.h"    


#include "USART_M.h"
#include "MDB_M.h"

 
 MDB_Byte MDB_BUFFER[37];
 uint8_t MDB_UART_BUFFER[MDB_UART_BUFFER_MAX];
 volatile uint8_t MDB_UART_BufferHead = 0;
 volatile uint8_t MDB_UART_BufferTail = 0;
 volatile uint16_t MDB_BUFFER_COUNT = 0;
 
 uint8_t EXT_UART_BUFFER[32];
 volatile uint8_t EXT_UART_BufferHead = 0;
 volatile uint8_t EXT_UART_BufferTail = 0;
 volatile uint8_t EXT_UART_BUFFER_COUNT = 0;
 volatile uint8_t EXTCMDCOMPLETE = 0;

/* Local utility function - 1ms delay loop (keeps original API) */
void delay_1ms(uint16_t ms) {
    volatile uint16_t i;
    for (i = 0; i < ms; i++) {
        _delay_ms(1);
    }
}

/* ----------------- MDB UART setup (9-bit, 9600, N,1) ----------------- */
void MDB_Setup(void)
{
    /* Baudrate */
    MDB_BAUD = (uint16_t)((float)F_CPU * 64.0f / (16.0f * 9600.0f) + 0.5f);

    
	 PORTC.DIRSET = PIN0_bm;   // TX amilek:added
	 PORTC.DIRCLR = PIN1_bm;   // RX amilek:added

/* CTRLC: asynchronous, no parity, 1 stop bit, CHSIZE = 9-bit base (low byte first) */
MDB_CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_1BIT_gc |  (6 << USART_CHSIZE_gp);  ;

    /* CTRLB: enable TX and RX; to get 9-bit mode we set UCSZ2 bit (bit position differs by device) */
    MDB_CTRLB = USART_TXEN_bm | USART_RXEN_bm; // amilek removed| USART_RXMODE_NORMAL_gc;
    /* Set 9-bit mode by setting UCSZ2 (the high bit of character size).
        On megaAVR0 series the UCSZ bits are split between CTRLC(CHSIZE) and CTRLB(UCSZ2 bit position).
        The macro below sets the UCSZ2 bit in CTRLB if defined; otherwise adjust per device headers.
     */
//  #ifdef USART_CHSIZE_9BIT_gc amilek:not necessary
//    
//      MDB_CTRLB |= USART_CHSIZE_9BIT_gc;
//  #else
     /* Generic: set the UCSZ2 bit if defined (this macro name may differ between IO headers).
        Many headers expose USART_RXMODE_NORMAL_gc and the UCSZ2 bit via CTRLB bit position USART_CHSIZE_gp etc.
        Here we set the bit manually if the bit position macro exists.
//      */
//  #ifdef USART_RXMODE0_bp
//  #error aaaaaaaaa
//      /* This was suggested earlier — if your header defines USART_RXMODE0_bp or similar for UCSZ2 */
//    MDB_CTRLB |= (1 << USART_RXMODE0_bp);
//  #else
//      /* Fallback: try common bit name for UCSZ2 */
//  #ifdef USART_CHSIZE_gm
//      /* no-op; rely on CTRLC CHSIZE + CTRLB default */
//  #else
//      /* If your header doesn't provide a way to set UCSZ2, you may need to consult your device header
//         and replace the above with the correct bit mask for 9-bit mode. */
//  #endif
//  #endif
// #endif 

    /* Clear RX/TX data registers flags if needed */
    (void)MDB_RXDATAL;
    (void)MDB_RXDATAH;
}

/* ----------------- EXT (external UART used for logs) ----------------- */

/* Transmit a NUL-terminated string on EXT UART (ASCII-safe) */
void EXT_UART_Transmit(uint8_t data[])
{
	while (*data)
	{
		char ch = *data++;
		if ((ch >= 32 && ch != 127) || ch == '\r' || ch == '\n')
		{
			/* wait for Data Register Empty */
			while (!(EXT_STATUS & EXT_DRE_IF)) {
			//	DIAGLED_FLASH(2);
			}

			/* send byte with 9th bit = 0 */
			
			EXT_TXDATAL = (uint8_t)ch; //switched due to the atmega4808 documentation
			EXT_TXDATAH = 0x00;
			//EXT_TXDATAL = (uint8_t)ch;
		}
		else
		{
			break;
		}
	}
}

void EXT_UART_Transmit_S(char* string){
	EXT_UART_Transmit((uint8_t*)string);
}


/* Send CRLF on EXT */
void EXT_CRLF(void)
{
    EXT_UART_Transmit_S("\r\n");
}

/* EXT UART setup (e.g. 8N1, 115200 or configured BAUD via config.h) */
void EXT_UART_Setup(void)
{
    /* Set EXT baud using MYUBRR formula or use the helper macro */
    EXT_BAUD = (uint16_t)((float)F_CPU * 64.0f / (16.0f * (float)UART_BAUD) + 0.5f);

    /* CTRLC: async, no parity, 1 stop bit, 8-bit chars (base) */
    EXT_CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_1BIT_gc | (0x03 << USART_CHSIZE_gp);

	PORTA.DIRSET = PIN0_bm; //wmilek: added
	
    /* CTRLB: enable tx/rx and RX interrupt if desired */
    EXT_CTRLB = USART_TXEN_bm | USART_RXEN_bm;
    /* enable RX Complete Interrupt for EXT UART */
    EXT_CTRLA |= USART_RXCIE_bm;

    sei(); /* enable global interrupts */
}

/* convenience helpers */
void EXT_UART_OK(void)   { EXT_UART_Transmit_S("OK\r\n"); }
void EXT_UART_NAK(void)  { EXT_UART_Transmit_S("NAK\r\n"); }
void EXT_UART_FAIL(void) { EXT_UART_Transmit_S("FAIL\r\n"); }

/* ----------------- EXT UART RX ISR (message assembly) -----------------
   The ISR name uses EXT_RXC_vect macro from mdb_usart.h (maps to correct vector)
*/
ISR(EXT_RXC_vect)
{
    uint8_t tmp = (uint8_t)EXT_RXDATAL;
    if (EXTCMDCOMPLETE == 0)
    {
        if (tmp == '+')  /* 0x2b */
        {
            EXTCMDCOMPLETE = 1;
        }
        else
        {
            if (EXT_UART_BUFFER_COUNT >= 32) EXT_UART_BUFFER_COUNT = 0;
            EXT_UART_BUFFER[EXT_UART_BUFFER_COUNT++] = tmp;
        }
    }
}

/* ----------------- MDB receive/send helpers (9-bit aware) ----------------- */

/* Blocking receive of one 9-bit word from MDB with ~20 ms timeout.
   Returns: 16-bit value where bit8 is MODE/9th-bit, low byte is data.
   On timeout sets MDBReceiveErrorFlag and MDBReceiveComplete.
*/
int MDB_Receive(void)
{
    uint16_t timeout = 0;

    /* wait for RX Complete (with timeout) */
    while (!(MDB_STATUS & MDB_RXC_IF) && (timeout < 20))
    {
        _delay_ms(1);
        timeout++;
    }

    if (timeout >= 20)
    {
        MDBReceiveErrorFlag = 1;
        MDBReceiveComplete = 1;
       // return -1; amilek:will see /* indicate error */
    }

    /* read 8-bit data and 9th bit */
    uint8_t low = (uint8_t)MDB_RXDATAL;
    uint8_t high = (uint8_t)(MDB_RXDATAH & 0x01);
    int ret = ((high << 8) | low);
    return ret;
}

/* Fill an MDB_Byte structure from one received 9-bit word */
void MDB_getByte(MDB_Byte *mdbb)
{
    int b = MDB_Receive();
	memcpy (mdbb, &b, 2);
    //if (b < 0) {
        /* error */
        //mdbb->data = 0;
      //  mdbb->mode = 0;
    //} else {
       // mdbb->data = (uint8_t)(b & 0xFF);
     //   mdbb->mode = (uint8_t)((b >> 8) & 0x01);
   // }
}

/* Simple checksum validator (last byte equals sum low 8 bits) */
uint8_t MDB_ChecksumValidate() {
	int sum = 0;
	for (int i=0; i < (MDB_BUFFER_COUNT-1); i++)
	sum += MDB_BUFFER[i].data;
	if (MDB_BUFFER[MDB_BUFFER_COUNT-1].data == (sum & 0xFF))
	return 1;
	else
	return 0;
}


void MDB_read(void)
{
    if (MDB_BUFFER_COUNT >= MDB_BUFFER_MAX) {
        /* overflow protection */
        MDBReceiveComplete = 1;
        MDBReceiveErrorFlag = 1;
        return;
    }

    MDB_getByte(&MDB_BUFFER[MDB_BUFFER_COUNT++]);

    /* safety cap (original used 37) */
    if (MDB_BUFFER_COUNT >= MDB_BUFFER_MAX) {
        MDBReceiveComplete = 1;
        MDBReceiveErrorFlag = 1;
        
    }

    /* If last received had mode==1 and checksum validates -> frame complete */
	if ((MDB_BUFFER[MDB_BUFFER_COUNT - 1].mode == 1) & (MDB_ChecksumValidate() == 1)){
		MDBReceiveComplete = 1;
	}

}


void MDB_Send(uint8_t data[], uint8_t len)
{
    MDBReceiveErrorFlag = 0;
    MDBReceiveComplete = 0;
    MDB_BUFFER_COUNT = 0;

    if (len == 0) return;

    /* send first byte with 9th bit = 1 */
    while (!(MDB_STATUS & MDB_DRE_IF)) { }
		MDB_TXDATAL = data[0]; //amilek: switched the order because of the atmega4808 doc 23.3.2.3 
		MDB_TXDATAH = 0x01;      /* 9th bit = 1 */
    

    /* send remaining bytes with 9th bit = 0 */
    for (uint8_t i = 1; i < len; ++i)
    {
        while (!(MDB_STATUS & MDB_DRE_IF)) { }
			
			MDB_TXDATAL = data[i]; //amilek: switched the order because of the atmega4808 doc 23.3.2.3
			MDB_TXDATAH = 0x00;
    }
}

/* MDB_ACK() - send ACK (0x00) with 9th bit = 0 (matches original code that cleared TXB8) */
void MDB_ACK(void)
{
    while (!(MDB_STATUS & MDB_DRE_IF)) { }
    MDB_TXDATAL = 0x00; //amilek: switched the order because of the atmega4808 doc 23.3.2.3
	MDB_TXDATAH = 0x00;
    
}

