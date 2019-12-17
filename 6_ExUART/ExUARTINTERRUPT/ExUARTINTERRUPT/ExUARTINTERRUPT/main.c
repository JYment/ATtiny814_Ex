/*
 * ExUARTINTERRUPT.c
 *
 * Created: 19-11-29 금 오전 10:07:11
 * Author : LABC
 */ 

#define F_CPU	3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usart_int.h"

int main(void)
{
    PORTA.DIRSET	= _BV(1);
	PORTA.OUTCLR	= _BV(1);
	PORTA.DIRCLR	= _BV(2);
	PORTA.PIN2CTRL	&= ~PORT_PULLUPEN_bm;
	PORTMUX.CTRLB	|= PORTMUX_USART0_bm;
	
	USART_0_init();
	
	PORTA.DIRSET	= _BV(3);
	
	sei();
	USART_0_enable();
    while (1) 
    {
		for(char c = 'A';;)
		{
			USART_0_write(c);
			while(!USART_0_is_rx_ready());
			c = USART_0_read();
			if(c == '\r')	USART_0_write('\n');
			else            c++;
			_delay_ms(100);
		}
    }
}

