/*
 * ExTimerb_oneshoot.c
 *
 * Created: 19-11-27 수 오후 02:32:34
 * Author : LABC
 */ 

#define F_CPU		3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/delay.h>


ISR(TCB0_INT_vect)
{
	PORTA.OUTCLR	= _BV(3);
	TCB0.INTFLAGS	= 0xFF;
}


int main(void)
{
    PORTA.DIRSET	= _BV(3);
	
	TCB0.CTRLB		= TCB_CNTMODE_SINGLE_gc;
	TCB0.INTCTRL	= TCB_CAPT_bm;
	
	sei();
    while (1) 
    {
		TCB0.CTRLA	&= ~TCB_ENABLE_bm;
		TCB0.CCMP	= 65535;
		TCB0.CNT	= 0;
		TCB0.CTRLA	= TCB_ENABLE_bm;
		
		PORTA.OUTSET	= _BV(3);
		_delay_ms(1000);
    }
}

