#ifndef USART_M_H
#define USART_M_H

#include <avr/io.h>
#include <stdint.h>
#include "MDB_M.h"
/* ---------- Buffers ---------- */
#define MDB_UART_BUFFER_MAX  64
extern uint8_t EXT_UART_BUFFER[32];
extern volatile uint8_t EXT_UART_BUFFER_COUNT;
extern volatile uint8_t EXTCMDCOMPLETE;

/* MDB receiving flags */
extern volatile uint8_t MDBReceiveComplete;
extern volatile uint8_t MDBReceiveErrorFlag;

void MDB_Setup(void);
void EXT_UART_Setup(void);
void EXT_UART_Transmit(uint8_t data[]);
void EXT_CRLF(void);
void EXT_UART_FAIL(void);
void EXT_UART_OK(void);
void EXT_UART_NAK(void);
void EXT_UART_UNK(void);
void EXT_UART_UNK_DATA(void);
void MDB_ACK(void);
void MDB_Send(uint8_t data[], uint8_t len);
void MDB_read(void);
void EXT_UART_Transmit_S(const char* string);
void EXT_UART_Transmit_UN(const uint8_t data[], size_t size);
void EXT_UART_Transmit_SN(const char* string, size_t maxlen);
void EXT_UART_Transmit_HEXDUMP(const char *prefix, const void *p, size_t size);
int MDB_Receive(void);
void delay_1ms(uint16_t ms);
#define EXT_RXC_vect        USART0_RXC_vect
#define EXT_DRE_vect        USART0_DRE_vect

#endif /* USART_M_H */
