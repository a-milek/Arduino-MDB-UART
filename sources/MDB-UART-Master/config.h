#ifndef CONFIG_H
#define CONFIG_H

#define F_CPU 33333333UL
#define UART_BAUD 9600
#define MYUBRR ((F_CPU/16/UART_BAUD)-1)

#endif