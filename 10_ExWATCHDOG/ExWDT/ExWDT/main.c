/*
 * ExWDT.c
 *
 * Created: 19-12-02 월 오후 02:25:58
 * Author : LABC
 */ 

/*
	A3 --- LED --- GND
	
	while문 속의 _PROTECTED_WRITE 를 리마크 처리하면 계속 재 부팅으로 LED 점멸
	-----_____-----_____-----_____ ....   길게 점멸(재부팅에 의한 점멸)
	
	while문 속에 _PROTECTED_WRITE 를 살리면 while 루프로 LED 점멸
	-----____-____-____-____-____  ....   짧게 점멸(while문 무한루프)
*/

#define F_CPU		3333333UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    _PROTECTED_WRITE(WDT_CTRLA, WDT_PERIOD_2KCLK_gc);
	PORTA.DIRSET = _BV(3);
	PORTA.OUTSET = _BV(3);
	_delay_ms(1000);
	
    while (1) 
    {
//		_PROTECTED_WRITE(WDT_CTRLA, WDT_PERIOD_2KCLK_gc);
		PORTA.OUTCLR = _BV(3);
		_delay_ms(1000);
		PORTA.OUTSET = _BV(3);
		_delay_ms(100);		
    }
}

