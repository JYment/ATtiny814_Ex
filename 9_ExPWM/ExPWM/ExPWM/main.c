/*
 * ExPWM.c
 *
 * Created: 19-12-02 월 오후 01:09:25
 * Author : LABC
 */ 

/* 
	PA3 / B0(WO0) -- LED -- GND
	PA1 / B0(WO0) -- LED -- GND
	PA2 / B0(WO0) -- LED -- GND
*/

#define F_CPU	3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/delay.h>



int main(void)
{
//	PORTA.DIR	= 0xFF;
    PORTB.DIR	= 0xFF;			// Attiny814

	// CMP0 ~ 2 Enable, PWM Enable
	TCA0.SINGLE.CTRLB	= TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_CMP1EN_bm | TCA_SINGLE_CMP2EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
	// TimerA Enable
	TCA0.SINGLE.CTRLA	= TCA_SINGLE_CLKSEL_DIV64_gc | TCA_SINGLE_ENABLE_bm;
	TCA0.SINGLE.PER		= 0xFF;			// TimerA의 주파수 = 3333333/(64*256) = 203Hz
    
	while (1) 
    {
		// 밝기가 변하는 주기는 CMP0 = 16 * 80ms = 1.28초
		for(uint8_t i=0; ; i+=16)
		{
			TCA0.SINGLE.CMP0	= i;
			TCA0.SINGLE.CMP1	= (i*2) & 0xFF;		// CMP0 주기의 2배
			TCA0.SINGLE.CMP2	= (i*4) & 0xFF;		// CMP0 주기의 4배
			_delay_ms(80);			
		}
    }
}
