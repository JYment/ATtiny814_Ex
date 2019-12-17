/*
 * ExADC.c
 *
 * Created: 19-11-27 수 오후 03:08:48
 * Author : LABC
 */ 

/*
	VCC 전압 측정 
	Internal VREF 사용
	run) 0.5V 단위로 LED 점멸
	ex)  9번 깜빡이면 4.5V
*/

#define F_CPU		3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>


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
    float value = 0;
	
	// VREF_0_init
	VREF.CTRLA	= VREF_ADC0REFSEL_1V1_gc;
	VREF.CTRLB	= VREF_ADC0REFEN_bm;
	
	// ADC_0_initiallization
	ADC0.MUXPOS	= ADC_MUXPOS_INTREF_gc;
	ADC0.CTRLC	= ADC_PRESC_DIV4_gc | ADC_REFSEL_VDDREF_gc;		// Vdd(Vcc) be ADC reference
	
	ADC0.CTRLA	= ADC_ENABLE_bm | ADC_FREERUN_bm;		// enable freerun, 10bit(default)
	ADC0.COMMAND |= 1;		// Start running ADC
	
    while (1) 
    {
		if(ADC0.INTFLAGS)
		{
			value = (0x400 * 1.1) / ADC0.RES;		// Calcurat the Vcc value
		}
		blink((uint8_t) value * 2.0);
    }
}

