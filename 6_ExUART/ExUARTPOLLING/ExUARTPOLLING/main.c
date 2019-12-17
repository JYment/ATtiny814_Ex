/*
 * ExUARTPOLLING.c
 *
 * Created: 19-11-28 목 오후 05:01:25
 * Author : LABC
 */ 

#define F_CPU		3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include "usart_poll.h"

int main(void)
{
    PORTA.DIRSET	=  _BV(1);
	PORTA.OUTSET	=  _BV(1);
	PORTA.DIRCLR	=  _BV(2);
	PORTA.PIN2CTRL	=  PORT_PULLUPEN_bm;
	PORTMUX.CTRLB	|= PORTMUX_USART0_bm;
	
	USART_0_init();
	PORTA.DIRSET	=  _BV(3);
	
	USART_0_enable();
	
    while (1) 
    {
		for(char c = 'A';;)
		{
			PORTA.OUTTGL = _BV(3);
			USART_0_write(c);
			while(!(USART_0_is_rx_ready()));
			c = USART_0_ready();
			
			if(c != '\r')	c++;
			else USART_0_write('\n');
			_delay_ms(100);
		}
    }
}

