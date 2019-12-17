/*
 * ExUSERROW.c
 *
 * Created: 19-12-02 월 오후 04:50:12
 * Author : LABC
 */ 

/*  
	attiny 1-series user row 읽기,쓰기
 
	회로구성
	A3---LED>]--(1k)---GND
 
	동작:
	ㅇ전원을 켜면 user row영역의 첫번째 데이터를 읽어서 +23 증가시킨 후
	ㅇ저장하고 다시 읽어서 그 값만큼 LED를 깜빡인다.
 
	LED표시:
	 t:_____-----_____-----
	 1:__   |
	 5:_ _ _ _ _ |
	 10:_________     |
	 50:..............     |
 
	* 저장된 데이터는 프로그래머에서 읽어서 확인할 수도 있다
*/
 

#define F_CPU		3333333UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>

uint8_t EEMEM eep_data, *user_row;

#define blink(n)		blink_n(&PORTA, 3, n)


void blink_n(PORT_t *port, int8_t pin_number, uint8_t n)
{
	#define L0(t)	port->OUTCLR = _BV(pin_number);	_delay_ms(t)
	#define L1(t)	port->OUTSET = _BV(pin_number);	_delay_ms(t)
	uint8_t i;
	
	port->DIRSET = _BV(pin_number);
	while(n >= 50)		// 2000ms
	{
		for(i=0; i<25; i++)
		{
			L1(30);
			L0(30);
		}
		L0(500);
		n -= 50;
	}
	
	while(n >= 10)		// 1500ms
	{
		L1(1000);
		L0(500);
		n -= 10;
	}
	
	if(n >= 5)			// 1000ms
	{
		for(i=0; i<5; i++)
		{
			L1(50);
			L0(50);
		}
		L0(500);
		n -= 5;
	}
	
	while(n--)			// 500ms
	{
		L1(100);
		L0(400);
	}
	
	L0(1000);
	#undef L0
	#undef L1	
}


int main(void)
{
    uint8_t c;
	user_row = &eep_data - 0x100;
	c = eeprom_read_byte(user_row);
	eeprom_write_byte(user_row, c+23);
	c = eeprom_read_byte(user_row);
	
    while (1) 
    {
		blink(c);
		_delay_ms(1000);
    }
}

