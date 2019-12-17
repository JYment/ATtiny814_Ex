/*
 * ExRTC.c
 *
 * Created: 19-11-27 수 오후 02:27:40
 * Author : LABC
 */ 

#define F_CPU		3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>


#define TERM		500


ISR(RTC_CNT_vect)
{
	PORTA.OUTTGL = _BV(3);
	RTC.INTFLAGS = RTC_OVF_bm;
}


int main(void)
{
	PORTA.DIRSET = _BV(3);
	
	while(RTC.STATUS > 0);		// Wait for all register to be synchronized
	RTC.CNT = 0;
	RTC.PER = (uint16_t) (TERM * 32.768);
	RTC.INTCTRL = RTC_OVF_bm;
	RTC.CTRLA	= RTC_RTCEN_bm;
	
	sei();
    while (1) 
    {
    }
}

