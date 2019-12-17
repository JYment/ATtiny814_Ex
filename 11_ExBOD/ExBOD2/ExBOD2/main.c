/*
 * ExBOD2.c
 *
 * Created: 19-12-02 월 오후 04:15:54
 * Author : LABC
 */ 

/*  
	attiny 1-series BOD
 
	[tiny를 파서로 이용시]
	tiny(bod)        tiny(파서)
	VCC <----------- A6
	A3  -----------> A1....A3 ----LED>]--(1k)--GND(저전압 경고)
	A7  -----------> A2....A7 ----LED>]--(1k)--GND
	GND ------------ GND
 
	BOD를 테스트하기 위하여 DAC로 가변전원을 구성하고,
	LED신호를 받아서 대신 켜준다.
 
	DAC 전압 도달시간
	0초        4.34V
	3초        3.8V
	6초        3.3V
	9초        2.0V
	12초       0.0V
*/

#define F_CPU		3333333UL
#include <avr/io.h>
#include <util/delay.h>


void led(void)
{
	if(PORTA.IN & _BV(1))		PORTA.OUTSET = _BV(3);
	else						PORTA.OUTCLR = _BV(3);
	if(PORTA.IN & _BV(2))		PORTA.OUTSET = _BV(7);
	else						PORTA.OUTCLR = _BV(7);
}


int main(void)
{
    PORTA.DIRCLR = _BV(6) | _BV(3) | _BV(4);
	PORTA.PIN6CTRL = 0;
	PORTA.DIRSET = _BV(3) | _BV(7);
	
	//VREF_0_init
	VREF.CTRLA = VREF_DAC0REFSEL_4V34_gc;
	VREF.CTRLB = VREF_DAC0REFEN_bm;
	// 4.34V(255)  3.8V(223)  3.3V(194)  2.0V(118)  0V(0)
	
	DAC0.CTRLA = DAC_ENABLE_bm | DAC_OUTEN_bm;
	
	uint8_t i;
	i = 255;
	
	// 3.8V까지
	while(i-- > 223)
	{
		DAC0.DATA = i;
		_delay_ms(3000/(255-223+1));
		led();
	}
	
	// 3.3V까지
	while(i-- > 194)
	{
		DAC0.DATA = i;
		_delay_ms(3000/(223-194+1));
		led();
	}
	
	// 2.0V까지
	while(i-- > 118)
	{
		DAC0.DATA = i;
		_delay_ms(3000/(194-118+1));
		led();
	}
	
	// 3.3V까지
	while(i-- > 0)
	{
		DAC0.DATA = i;
		_delay_ms(3000/(223-194+1));
		led();
	}

	DAC0.DATA = 0;

	
    while (1) 
    {
    }
}

