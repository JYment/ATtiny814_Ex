/*
 * ExADC2.c
 *
 * Created: 19-11-27 수 오후 04:34:59
 * Author : LABC
 */ 

#define F_CPU		3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

/*
	// ADC0
*/

void blink(uint8_t n)
{
	uint8_t i;
	PORTA.DIRSET = _BV(3);
	for(i=0; i<2*n; i++)
	{
		PORTA.OUTTGL = _BV(3);
		_delay_ms(200);
	}
	_delay_ms(1000);
}


int main(void)
{
    ADC0.CTRLA	= ADC_ENABLE_bm;
	ADC0.CTRLC	= ADC_PRESC_DIV4_gc | ADC_REFSEL_VDDREF_gc;
	ADC0.MUXPOS = ADC_MUXPOS_AIN7_gc;
	
    while (1) 
    {
		ADC0.COMMAND = ADC_STCONV_bm;
		while((ADC0.INTFLAGS & ADC_RESRDY_bm) == 0);
		blink(ADC0.RES / 94);
    }
}

