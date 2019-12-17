/*
 * ExTimer.c
 *
 * Created: 19-11-27 수 오전 11:49:47
 * Author : LABC
 */ 

#define F_CPU	3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

#define TERM		500

ISR(TCA0_OVF_vect)
{
	PORTA_OUTTGL = _BV(3);
	TCA0.SINGLE.INTFLAGS |= TCA_SINGLE_OVF_bm;
}


int main(void)
{
    PORTA.DIRSET = _BV(3);
	
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1024_gc | TCA_SINGLE_ENABLE_bm;
	TCA0.SINGLE.PER = (uint16_t) (((F_CPU / 1000) * TERM) / 1024 - 1);
	
	sei();
    while (1) 
    {
    }
}

