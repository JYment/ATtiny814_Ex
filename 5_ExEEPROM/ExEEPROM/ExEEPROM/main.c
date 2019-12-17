/*
 * ExFlash.c
 *
 * Created: 19-11-28 목 오전 10:26:42
 * Author : LABC
 */ 

/*
	전원을 켜면 program영역 데이터를 읽는다. 제대로 읽혔는지 LED로 표시하게 하였다.
	program영역 데이터가 제대로 읽혀졌으면 eeprom 데이터를 읽어서 1증가시켜 저장한다
	다음 LED를 eeprom 데이터 % 3 + 1 회 만큼 깜박거린다
	[출처] [강좌#8]AVR tiny-1:flash 와 eeprom (당근이의 AVR 갖구 놀기) |작성자 깐따삐약
*/


#define F_CPU		3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

const uint8_t pgm_data[] PROGMEM = {1, 2, 3, 4};		// program 영역 데이터, 읽기만 가능
uint8_t EEMEM eep_data;									// eeprom 영역


void blink(uint8_t n)
{
	uint8_t i;
	PORTA.DIRSET = _BV(3);
	for(i=0; i<2*n; i++)
	{
		PORTA.OUTTGL = _BV(3);
		_delay_ms(250);
	}
	_delay_ms(500);
}


int main(void)
{
    uint8_t c, p;
	
	p = pgm_read_byte(&pgm_data[2]);		// p=3 플래시는 쉽게 읽을 수 있지만 eep처럼 쉽게 쓸수는 없음
	if(p != 3)								// p=3일 것이다. 만일 아니면 LED를 빠르게 점멸하고 진행하지 않음
	{
		PORTA.DIRSET = _BV(3);
		while(1)
		{
			PORTA.OUTTGL = _BV(3);
			_delay_ms(50);
		}
	}
	
	c = eeprom_read_byte(&eep_data);		// eeprom 값을 읽음
	c++;									
	eeprom_write_byte(&eep_data, c);		// 다시 저장. 전원을 다시 실행시키면 1씩 증가되어 있음
    while (1) 
    {
		blink((c%3)+1);
    }
}

