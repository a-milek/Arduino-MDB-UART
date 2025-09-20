#ifndef MDB_USART_H
#define MDB_USART_H

#include <avr/io.h>

/* ---------- Select which USART is MDB and which is EXT ---------- */
#define MDB_USART   USART1
#define EXT_USART   USART0

/* ---------- Baudrate calculation ---------- */
#define USART_BAUD(F_CPU, BAUD) ((uint16_t)((float)(F_CPU) * 64 / (16 * (BAUD)) + 0.5))

/* ---------- MDB macros ---------- */
#define MDB_BAUD        MDB_USART.BAUD
#define MDB_CTRLA       MDB_USART.CTRLA
#define MDB_CTRLB       MDB_USART.CTRLB
#define MDB_CTRLC       MDB_USART.CTRLC
#define MDB_STATUS      MDB_USART.STATUS
#define MDB_TXDATAL     MDB_USART.TXDATAL
#define MDB_TXDATAH     MDB_USART.TXDATAH
#define MDB_RXDATAL     MDB_USART.RXDATAL
#define MDB_RXDATAH     MDB_USART.RXDATAH

#define MDB_ENABLE_TX()     (MDB_CTRLB |= USART_TXEN_bm)
#define MDB_ENABLE_RX()     (MDB_CTRLB |= USART_RXEN_bm)
#define MDB_DISABLE_TX()    (MDB_CTRLB &= ~USART_TXEN_bm)
#define MDB_DISABLE_RX()    (MDB_CTRLB &= ~USART_RXEN_bm)

/* Status bits (from io.h) */
#define MDB_DRE_IF      USART_DREIF_bm 
#define MDB_RXC_IF      USART_RXCIF_bm

/* ---------- EXT macros ---------- */
#define EXT_BAUD        EXT_USART.BAUD
#define EXT_CTRLA       EXT_USART.CTRLA
#define EXT_CTRLB       EXT_USART.CTRLB
#define EXT_CTRLC       EXT_USART.CTRLC
#define EXT_STATUS      EXT_USART.STATUS
#define EXT_TXDATAL     EXT_USART.TXDATAL
#define EXT_TXDATAH     EXT_USART.TXDATAH
#define EXT_RXDATAL     EXT_USART.RXDATAL
#define EXT_RXDATAH     EXT_USART.RXDATAH

#define EXT_ENABLE_TX()     (EXT_CTRLB |= USART_TXEN_bm)
#define EXT_ENABLE_RX()     (EXT_CTRLB |= USART_RXEN_bm)
#define EXT_DISABLE_TX()    (EXT_CTRLB &= ~USART_TXEN_bm)
#define EXT_DISABLE_RX()    (EXT_CTRLB &= ~USART_RXEN_bm)

/* Status bits */
#define EXT_DRE_IF      USART_DREIF_bm
#define EXT_RXC_IF      USART_RXCIF_bm

/* ---------- Interrupt vectors ---------- */
#define MDB_RXC_vect        USART1_RXC_vect
#define MDB_DRE_vect        USART1_DRE_vect
#define EXT_RXC_vect        USART0_RXC_vect
#define EXT_DRE_vect        USART0_DRE_vect

#endif /* MDB_USART_H */
