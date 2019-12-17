/*
 * ExSWUART.c
 *
 * Created: 19-11-28 목 오전 10:43:23
 * Author : LABC
 */ 

/*
	동작:
	시작하면 ABCD를 출력하고
	타이핑하는 키+1을 화면에 출력한다.

	printf를 사용하려면 USE_PRINTF 를 선언해야 한다.

	클럭오차가 크면 글자가 깨져 나올수 있다.
	클럭오차는 칩마다 달라서 calibration을 해야 하는데,
	그게 번거로우니 BIT_USEC 의 1000000 을 1050000 950000 등으로 바꾸어 보면
	적당한 값을 찾을 수 있다.
*/

#define F_CPU		3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include "sw_uart.h"


int main(void)
{
    int16_t c;
	
	init_uart((volatile uint8_t *) &PORTA, 3, 1);		// TX PORT : A3
	init_uart((volatile uint8_t *) &PORTA, 6, 0);		// RX PORT : A6
	
	puts("ABCDE\r\n");
	printf("i : %d\r\n", 1234);
	
	while(1)
	{
		do
		{
			c = getch();
		}
		while(c == -1);
		if(c != '\r')	c++;
		putch(c);
		if(c == '\r')	putch('\n');
	}
	
	return 0;
}
