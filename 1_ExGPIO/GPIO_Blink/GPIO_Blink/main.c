/*
 * GPIO_Blink.c
 *
 * Created: 19-11-27 수 오전 09:29:15
 * Author : LABC
 */ 

#define F_CPU	3333333UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	// EX) PORTn.DIRSET = _BV(핀번호);
	// --------- DIRSET = 출력
	// --------- DIRCLR = 입력
	PORTA.DIRSET = _BV(1);
    
    while (1) 
    {
		// EX) PORTn.OUTSET = _BV(핀번호);
		// ----------OUTSET = HIGH
		// ----------OUTCLR = LOW
		PORTA.OUTSET = _BV(1);
//		_delay_ms(1000);
// 		PORTA.OUTCLR = _BV(1);
// 		_delay_ms(1000);
    }
}

