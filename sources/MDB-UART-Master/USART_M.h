#ifndef USART_M_H
#define USART_M_H

#include <avr/io.h>
#include <stdint.h>
#include "MDB_M.h"
/* ---------- Select which USART is MDB and which is EXT ---------- */
#define MDB_USART   USART1
#define EXT_USART   USART0

/* ---------- Baudrate calculation ---------- */
//#define USART_BAUD(F_CPU, BAUD) ((uint16_t)((float)(F_CPU) * 64 / (16 * (BAUD)) + 0.5))

// /* ---------- MDB macros ---------- */
// #define MDB_BAUD      MDB_USART.BAUD
// #define MDB_CTRLA     MDB_USART.CTRLA
// #define MDB_CTRLB     MDB_USART.CTRLB
// #define MDB_CTRLC     MDB_USART.CTRLC
// #define MDB_STATUS    MDB_USART.STATUS
// #define MDB_TXDATAL   MDB_USART.TXDATAL
// #define MDB_TXDATAH   MDB_USART.TXDATAH
// #define MDB_RXDATAL   MDB_USART.RXDATAL
// #define MDB_RXDATAH   MDB_USART.RXDATAH
// 
// #define MDB_ENABLE_TX()     (MDB_CTRLB |= USART_TXEN_bm)
// #define MDB_ENABLE_RX()     (MDB_CTRLB |= USART_RXEN_bm)
// #define MDB_DISABLE_TX()    (MDB_CTRLB &= ~USART_TXEN_bm)
// #define MDB_DISABLE_RX()    (MDB_CTRLB &= ~USART_RXEN_bm)

//#define MDB_DRE_IF      (MDB_USART.DREIF_bm) amilek: declaration in USART_M_conf.h
//#define MDB_RXC_IF      (MDB_USART.RXCIF_bm)

/* ---------- EXT macros ---------- */
// #define EXT_BAUD      EXT_USART.BAUD
// #define EXT_CTRLA     EXT_USART.CTRLA
// #define EXT_CTRLB     EXT_USART.CTRLB
// #define EXT_CTRLC     EXT_USART.CTRLC
// #define EXT_STATUS    EXT_USART.STATUS
// #define EXT_TXDATAL   EXT_USART.TXDATAL
// #define EXT_TXDATAH   EXT_USART.TXDATAH
// #define EXT_RXDATAL   EXT_USART.RXDATAL
// #define EXT_RXDATAH   EXT_USART.RXDATAH

// #define EXT_ENABLE_TX()     (EXT_CTRLB |= USART_TXEN_bm)
// #define EXT_ENABLE_RX()     (EXT_CTRLB |= USART_RXEN_bm)
// #define EXT_DISABLE_TX()    (EXT_CTRLB &= ~USART_TXEN_bm)
// #define EXT_DISABLE_RX()    (EXT_CTRLB &= ~USART_RXEN_bm)

//#define EXT_DRE_IF      (EXT_USART.DREIF_bm)
//#define EXT_RXC_IF      (EXT_USART.RXCIF_bm)

/* ---------- Buffers ---------- */
#define MDB_UART_BUFFER_MAX  64
extern uint8_t EXT_UART_BUFFER[32];
//extern MDB_Byte MDB_BUFFER[37]; amilek: proper declaration in MDB_M.h
volatile uint8_t EXT_UART_BUFFER_COUNT;
//volatile uint8_t MDB_BUFFER_COUNT; amilek:duplicated declaration in MDB_M.h
volatile uint8_t EXTCMDCOMPLETE;


//MDB receiving flags
volatile uint8_t MDBReceiveComplete;  //MDB message receive completed flag
volatile uint8_t MDBReceiveErrorFlag;  //MDB message receive error flag
void MDB_Setup(void);
void EXT_UART_Setup(void);
void EXT_UART_Transmit(uint8_t data[]);

void EXT_CRLF(void);
void EXT_UART_FAIL(void);
void EXT_UART_OK(void);
void EXT_UART_NAK(void);
void MDB_ACK(void);
void MDB_Send(uint8_t data[], uint8_t len);
void MDB_getByte(MDB_Byte* mdbb);
void MDB_read(void);
void EXT_UART_Transmit_S(char* string);
uint8_t MDB_ChecksumValidate(void);
int MDB_Receive(void);
void delay_1ms(uint16_t ms);
#define EXT_RXC_vect        USART0_RXC_vect
#define EXT_DRE_vect        USART0_DRE_vect

#endif /* USART_M_H */
