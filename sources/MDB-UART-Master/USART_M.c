/*
 * USART_M.c
 *
 * Created: 18.05.2019 09:47:09
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

void MDB_Setup(void)
{
	// Baud rate 9600
	MDB_UBRRH = (MYUBRR>>8);
	MDB_UBRRL = MYUBRR;
	MDB_UCSR_A &= ~(1 << U2X0);// Disable USART rate doubler
	MDB_UCSR_C = (0<<UMSEL1)|(0<<UMSEL0)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0);
	MDB_UCSR_B |= (1<<UCSZ2)|(1<<RXEN)|(1<<TXEN); // 9bit
	USART1.CTRLC = USART_CMODE_ASYNCHRONOUS_gc |
	USART_PMODE_DISABLED_gc |
	USART_SBMODE_1BIT_gc;

	// Control B: enable RX and TX, 9-bit size
	 USART1.CTRLB = USART_TXEN_bm | USART_RXEN_bm | USART_RXMODE_NORMAL_gc;
	 USART1.CTRLB |= (1 << USART_RXMODE0_bp); // enable 9-bit (sets UCSZ2)}


void EXT_UART_Transmit(uint8_t data[])
{
	for (int i = 0; i < strlen(data); i++){
		/* Wait for empty transmit buffer */
		while (( UCSR1A & (1<<UDRE1))  == 0){};
		if ((data[i] >= 32 && data[i] != 127) || (data[i] == 0x0d || data[i] == 0x0a)) UDR1 = data[i]; else break;
	}
}

void EXT_CRLF()
{
	EXT_UART_Transmit("\r\n");
}

void EXT_UART_Setup()
{
	UBRR1H = (MYUBRR>>8);
	UBRR1L = MYUBRR;
	/* Set frame format: 8data, 2stop bit */
	UCSR1C |= (1<< UCSZ10)|(1<< UCSZ11);
	UCSR1B = (1 << TXEN1)|(1 << RXEN1)|(1<<RXCIE1);
	sei();
}

void EXT_UART_OK()
{
	EXT_UART_Transmit("OK\r\n");
}

void EXT_UART_NAK()
{
	EXT_UART_Transmit("NAK\r\n");
}

void EXT_UART_FAIL()
{
	EXT_UART_Transmit("FAIL\r\n");
}

void delay_1ms(uint16_t ms) {
	volatile uint16_t i,foo = 0;
	for(i=0;i<ms;i++)
	{
		_delay_ms(1);
		//make some "work" to avoid optimization
		foo++;
	}
	foo = 0;
}

ISR(USART1_RX_vect)
{
	uint8_t tmp = UDR1;
	if (EXTCMDCOMPLETE == 0)
	{
		if (tmp == 0x2b)
		{
			EXTCMDCOMPLETE = 1;
		} else
		{
			if (EXT_UART_BUFFER_COUNT == 32) 
			{
				EXT_UART_BUFFER_COUNT = 0;
			}
			EXT_UART_BUFFER[EXT_UART_BUFFER_COUNT++] = tmp;
		}
	}
}

int MDB_Receive() {
	uint8_t resh, resl;
	int rtr = 0;
	// Wait for data to be received, 20msec must fit...
	while ((!(UCSR0A & (1<<RXC0))) && rtr < 20) {
		delay_1ms(1);
		rtr++;
	}
	if (rtr == 20){//..otherwise this is an timeout behavior
		MDBReceiveErrorFlag = 1;
		MDBReceiveComplete = 1;
	}
	// Get 9th bit, then data from buffer
	resh = UCSR0B;
	resl = UDR0;
	// Filter the 9th bit, then return only data w\o mode bit
	resh = (resh >> 1) & 0x01;
	return ((resh << 8) | resl);
}

void MDB_getByte(MDB_Byte* mdbb) {
	int b = MDB_Receive();
	memcpy (mdbb, &b, 2);
}

uint8_t MDB_ChecksumValidate() {
	int sum = 0;
	for (int i=0; i < (MDB_BUFFER_COUNT-1); i++)
	sum += MDB_BUFFER[i].data;
	if (MDB_BUFFER[MDB_BUFFER_COUNT-1].data == (sum & 0xFF))
	return 1;
	else
	return 0;
}

void MDB_read() {
	MDB_getByte(&MDB_BUFFER[MDB_BUFFER_COUNT++]);
	if (MDB_BUFFER_COUNT == 37){
		MDBReceiveComplete = 1;
		MDBReceiveErrorFlag = 1;
	}
	if ((MDB_BUFFER[MDB_BUFFER_COUNT - 1].mode == 1) & (MDB_ChecksumValidate() == 1)){
		MDBReceiveComplete = 1;
	}
}


void MDB_Send(uint8_t data[], uint8_t len) {
	MDBReceiveErrorFlag = 0;
	MDBReceiveComplete = 0;
	MDB_BUFFER_COUNT = 0;
	while ( !( UCSR0A & (1<<UDRE0))) {};
	UCSR0B |= (1<<TXB80);
	UDR0 = data[0];
	for (int i = 1; i < len; i++)
	{
		while ( !( UCSR0A & (1<<UDRE0))) {};
		UCSR0B &= ~(1<<TXB80);
		UDR0 = data[i];
	}
}

void MDB_ACK() {
	while ( !( UCSR0A & (1<<UDRE0)));
	UCSR0B &= ~(1<<TXB80);
	UDR0 = 0x00;// send ACK to MDB if peripheral answer is not just *ACK*, otherwise peripheral will try to send unconfirmed data with next polls
	//MDBDebug();
}
