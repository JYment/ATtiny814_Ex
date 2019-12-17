/*
 * GPIO_INT.c
 *
 * Created: 19-11-27 수 오전 10:02:36
 * Author : LABC
 */ 

#define F_CPU	3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/delay.h>


volatile uint8_t flag;


ISR(PORTB_PORT_vect)
{
	if(PORTB.INTFLAGS & _BV(1))			flag = 1;			
	PORTB.INTFLAGS = _BV(1);		// PORTB1 INTFLAGS Clear
}


int main(void)
{
    PORTA.DIRSET = _BV(1);		// PORTA1 = OUTPUT
	PORTB.DIRCLR = _BV(1);		// PORTB1 = INPUT
	
	// INTERRUPT -> ISC0_bm			  : Both	edge
	// ------------ ISC1_bm			  : Rising	edge
	// ------------ ISC1_bm | ISC0_bm : Falling edge
	PORTB.PIN1CTRL |= PORT_PULLUPEN_bm | PORT_ISC0_bm;		// PORTB1 Pull up Enable, Both edges 
	
	sei();
    while (1) 
    {
		if(flag == 1)
		{
			PORTA.OUTTGL = _BV(1);
			_delay_ms(200);
			flag = 0;
		}
    }
}

