/*
 * ExTimerB.c
 *
 * Created: 19-11-27 수 오후 01:29:56
 * Author : LABC
 */ 

#define F_CPU		3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

#define TERM		10

ISR(TCB0_INT_vect)
{
	static uint8_t t = 0;
	if(++t >= 50)
	{
		PORTA.OUTTGL = _BV(3);
		t = 0;
	}
	TCB0.INTFLAGS = 0xFF;
}

int main(void)
{
#if 0
	TCB0.CTRLA	= TCB_ENABLE_bm;
	TCB0.CCMP	= F_CPU * TERM / 1000 - 1;
#else
	TCB0.CTRLA	= TCB_ENABLE_bm | TCB_CLKSEL_CLKDIV2_gc;
	TCB0.CCMP	= F_CPU * TERM / (1000 * 2) - 1;
#endif	
	TCB0.INTCTRL = TCB_CAPT_bm;
	
	sei();
	PORTA.DIRSET = _BV(3);
    while (1) 
    {
    }
}

