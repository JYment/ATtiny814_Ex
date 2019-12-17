/*
 * ExBOD.c
 *
 * Created: 19-12-02 월 오후 02:43:58
 * Author : LABC
 */ 

/*
	FUSE 설정
	
	BODCFG.ACTIVE 로 기능을 활성화 시키고
	BODCFG.LVL에서 전압을 지정하고,
	BODCFG.SAMPFREQ 에서 샘플링주파수 설정
	BODCFG.SLEEP 전압이 떨어졌을 때 sleep로 들어갈 것인지 지정

	A3 --- LED --- GND
	A7 --- LED --- GND
	

	퓨즈:BODCFG(1)=0x85
	enable 3.3V 1khz sleep enable

	동작:3.8V에 A3가 점멸하기 시작하고 3.3V가 되면 sleep로 들어간다.	
*/


#define F_CPU		3333333UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int8_t flag;

ISR(BOD_VLM_vect)
{
	flag = 1;
	BOD.INTFLAGS = BOD_VLMIE_bm;
}


int main(void)
{
	BOD.INTCTRL = BOD_VLMIE_bm | BOD_VLMCFG_ABOVE_gc;
	BOD.VLMCTRLA = BOD_VLMLVL_15ABOVE_gc;
	
	PORTA.DIRSET = _BV(3) | _BV(7);
	PORTA.OUTSET = _BV(3) | _BV(7);
	
	sei();
    while (1) 
    {
		if(flag)
		{
			PORTA.OUTTGL = _BV(3);
			_delay_ms(200);
		}
    }
}

