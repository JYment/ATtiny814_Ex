/*
 * sw_uart.h
 *
 * Created: 19-11-28 목 오전 10:57:55
 *  Author: LABC
 */ 


#ifndef SW_UART_H_
#define SW_UART_H_

#ifndef F_CPU
	#define F_CPU		3333333UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define USE_PRINTF
#define BAUD_RATE		9600

void init_uart(volatile uint8_t *port, uint8_t pin_bp, int8_t tx);

int16_t getch(void);
void putch(int16_t c);
void puth(uint8_t c);
void putb(uint8_t c);
void puti(int16_t i);
void putstr(char *s);
void putcr(void);

int uart_sw_test(void);



#endif /* SW_UART_H_ */