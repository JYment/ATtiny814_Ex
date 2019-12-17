/*
 * ExAC.c
 *
 * Created: 19-11-29 금 오후 01:31:39
 * Author : LABC
 */ 

/*
	A7에 공급되는 신호가 2.5V 보다 커지거나 작으면 LED가 반전
*/


#define	F_CPU		3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(AC0_AC_vect)
{
	PORTA.OUTTGL	= _BV(3);			// 인터럽트 발생시 PA3 토글
	AC0.STATUS		= AC_CMP_bm;
}


int main(void)
{
	// AINP0 설정
    PORTA.PIN7CTRL	= (PORTA.PIN7CTRL & ~PORT_ISC_gm) | PORT_ISC_INPUT_DISABLE_gc;
	PORTA.PIN7CTRL	&= ~PORT_PULLUPEN_bm;
	
	VREF.CTRLA	= VREF_DAC0REFSEL_2V5_gc;		// Vref 2.5v로 설정
	
	// DAC0 관련 설정
	// AC_ENABLE_bm						: Analog Comparator 0 enable
	// AC_HYSMODE1_bm | AC_HYSMODE0_bm	: hysteresis 50mV설정
	// AC_CMP_bm						: Analog Comparator 0 Interrupt Enable
	// AC_MUXNEG_VREF_gc				: AINN0은 A6을 대신하여 Vref(2.5v)사용
	// AC_MUXPOS_PIN0_gc				: AINP0는 A7을 사용
	AC0.CTRLA	= AC_ENABLE_bm | AC_HYSMODE1_bm | AC_HYSMODE0_bm;		
	AC0.INTCTRL	= AC_CMP_bm;
	AC0.MUXCTRLA	= AC_MUXNEG_VREF_gc | AC_MUXPOS_PIN0_gc;
	
	PORTA.DIRSET = _BV(3);
	PORTA.DIRSET = _BV(2);
	sei();
    while (1) 
    {
		PORTA.OUTTGL = _BV(2);
		_delay_ms(100);
    }
}

