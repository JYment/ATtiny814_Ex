/*
 * ExClkSet.c
 *
 * Created: 19-11-27 수 오전 11:14:06
 * Author : LABC
 */ 

#define F_CPU	20000000
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

int main(void)
{
	// Clock 설정
	// F_CPU = 20,000,000 -    20 MHz
	// ----- = 10,000,000 -    10 MHz
	// ----- =  5,000,000 -     5 MHz
	// ----- =  3,333,333 -	  3.3 MHz
	// ----- =    416,000 - 0.416 MHz
	
    _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, 0);		// 20MHz
// 	_PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, (CLKCTRL_PEN_bm | CLKCTRL_PDIV_2X_gc));		// 10MHz
// 	_PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, (CLKCTRL_PEN_bm | CLKCTRL_PDIV_4X_gc));		// 5MHz
// 	_PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, (CLKCTRL_PEN_bm | CLKCTRL_PDIV_6X_gc));		// 3.333..MHz
// 	_PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, (CLKCTRL_PEN_bm | CLKCTRL_PDIV_48X_gc));		// 0.416..MHz

	PORTA_DIRSET = _BV(3);
    while (1) 
    {
		PORTA.OUTTGL = _BV(3);
		_delay_ms(200);
    }
}

