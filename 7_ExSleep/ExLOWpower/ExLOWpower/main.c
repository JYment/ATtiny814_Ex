/*
 * ExLOWpower.c
 *
 * Created: 19-11-29 금 오전 10:32:04
 * Author : LABC
 */ 

#define F_CPU		16384
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

ISR(PORTA_PORT_vect)
{
	PORTA.INTFLAGS	= _BV(2);
}

int main(void)
{
    static uint8_t count = 0;
	
	// Lower Power 를 위한 설정
	// 1. 낮은 클럭설정(내부 32kHz)
	_PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, (CLKCTRL_PEN_bm | CLKCTRL_PDIV_2X_gc));
	_PROTECTED_WRITE(CLKCTRL_MCLKCTRLA, CLKCTRL_CLKSEL_OSCULP32K_gc);
	while(CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm);		// Wait for system oscillator changing to finish
	
	// 2. 사용하지 않는 핀은 pullup
	for(uint8_t i=0; i<8; i++)
	{
		*((uint8_t *)&PORTA + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
	}
	
	// 3. 가능한한 모든기능 off 필요한 기능이라도 쓸때만 켜서 쓰고 바로 끄기
	
	// 4. 낮은 전압구동
	
	PORTA.DIRSET = _BV(3);
	PORTA.DIRCLR = _BV(2);
	PORTA.PIN2CTRL	= PORT_PULLUPEN_bm | PORT_ISC1_bm | PORT_ISC0_bm;		// Falling edge
	
	// 5. Sleep으로 대기
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	
	sei();
    while (1) 
    {
		// 작동 확인용 코드 전력사용 무시하고 작성
		for(uint8_t i=0; i<=(count & 15); i++)
		{
			PORTA.OUTSET	= _BV(3);
			_delay_ms(250);
			PORTA.OUTCLR	= _BV(3);
			_delay_ms(250);
		}
		count++;
		_delay_ms(1000);
		
		// 작동 확인 끝
		
		sleep_cpu();
		// Sleep에서 깨어났을 때 이후 동작하는 코드 작성		
    }
}

