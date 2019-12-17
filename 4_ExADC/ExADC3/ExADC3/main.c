/*
 * ExADC3.c
 *
 * Created: 19-11-28 목 오전 09:39:39
 * Author : LABC
 */ 

/*
	ADC값을 폴링으로 읽는 것은 불편할 수도 있습니다.
	tiny1에서는 이벤트시스템(evsys)라는 것을 지원합니다.
	AVR에는 없는 기능이라 생소할 수 있는데, 주변장치와 주변장치간 신호 전달을 위하여 사용한다고 되어 있습니다.
	ADC는 전압을 읽는 주변장치이고,
	타이머는 주기적으로 어떤 일을 하게 할 수 있는 주변장치입니다.
	두가지를 묶어서 주기적으로 전압을 읽고 싶다, 이럴때 사용할 수 있습니다.
	[출처] [강좌#7]AVR tiny-1:DAC, ADC (당근이의 AVR 갖구 놀기) |작성자 깐따삐약
*/

#define	F_CPU		3333333UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

volatile int16_t val;

ISR(ADC0_RESRDY_vect)
{
	val = ADC0.RES;
}

ISR(TCB0_INT_vect)
{
	PORTA.OUTTGL	= _BV(1);
	TCB0.INTFLAGS	= 0xFF;
}


void blink(uint8_t n)
{
	uint8_t i;
	PORTA.DIRSET	= _BV(3);
	
	for(i=0; i<2*n; i++)
	{
		PORTA.OUTTGL	= _BV(3);
		_delay_ms(250);
	}
	_delay_ms(500);
}


int main(void)
{
	PORTA.DIRSET	= _BV(1);
	
	// TCB0 Timer
	TCB0.CCMP		= 50000;
	TCB0.CTRLA		= TCB_ENABLE_bm;
	TCB0.INTCTRL	= TCB_CAPT_bm;
	
	// ADC
	PORTA.DIRCLR	= _BV(7);		// ADC Input
	ADC0.CTRLA		= ADC_RESSEL_10BIT_gc | ADC_ENABLE_bm;		// ADC 10 Bit Resolution
	ADC0.CTRLC		= ADC_PRESC_DIV4_gc;		// Prescaler DIV 4
	ADC0.MUXPOS		= ADC_MUXPOS_AIN7_gc;		// ADC Input 7 (PA7)
	ADC0.EVCTRL		= ADC_STARTEI_bm;			// Start Event Input Enable (start conversion on event input)
	ADC0.INTCTRL	= ADC_RESRDY_bm;			// Enable ADC result ready interrupt
	ADC0.INTFLAGS	= 0xFF;						// Clear interrupt flags
	
	// Evsys
	EVSYS.SYNCCH0		= EVSYS_SYNCCH0_TCB0_gc;
//	EVSYS.ASYNCUSER1	= EVSYS_ASYNCUSER1_SYNCCH0_gc;
	
	sei();
	
	EVSYS.ASYNCUSER1 = EVSYS_ASYNCUSER1_SYNCCH0_gc;		// Enable event forwarding to ADC
    while (1) 
    {
		blink(val/94);
    }
	
	TCB0.CTRLA &= ~(TCB_ENABLE_bm);			// Timer Disable
	EVSYS.ASYNCUSER1 = 0;					// Evsys Disable
}

