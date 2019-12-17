/*
 * GPIO_INPUT.c
 *
 * Created: 19-11-27 수 오전 09:41:34
 * Author : LABC
 */ 

#define F_CPU	3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>		// #define _BV(bit)		(1 << bit)
#include <util/delay.h>

int main(void)
{
	// EX) PORTn.DIRSET = _BV(핀번호);
	// --------- DIRSET = 출력
	// --------- DIRCLR = 입력
	PORTA.DIRSET = _BV(1);
	PORTB.DIRCLR = _BV(1);
	
	
	PORTB.PIN1CTRL |= PORT_PULLUPEN_bm;		// Pull up Enable
	while (1)
	{
		// EX) PORTn.IN & _BV(핀번호) ::::: return 확인필요
		if(PORTB.IN & _BV(1))	PORTA.OUTSET = _BV(1);
		else					PORTA.OUTCLR = _BV(1);
	}
}
