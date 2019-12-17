/*
 * ExDAC.c
 *
 * Created: 19-11-27 수 오후 02:47:06
 * Author : LABC
 */ 

#define F_CPU		3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>


int main(void)
{
	// ATtiny814 - PORTA6 : DAC PIN
    PORTA.DIRCLR	= _BV(6);
	PORTA.PIN6CTRL	= 0;
	
	VREF.CTRLA = VREF_DAC0REFSEL_4V34_gc;
	VREF.CTRLB = VREF_DAC0REFEN_bm;
	
	DAC0.CTRLA = DAC_ENABLE_bm | DAC_OUTEN_bm;
	
    while (1) 
    {
		for(uint8_t i=0;i<256;i++)
		{
			DAC0.DATA = i;
			_delay_ms(10);
		}
    }
}

