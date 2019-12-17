/*
 * ExRESET.c
 *
 * Created: 19-12-02 월 오후 02:29:55
 * Author : LABC
 */ 

/*
	A3 --- LED --- GND
	LED 1번, 2번, 3번 동작 점멸 후
	SW-RESET 동작
*/

#define F_CPU		3333333UL
#include <avr/io.h>
#include <util/delay.h>


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
    uint8_t i;
    while (1) 
    {
		for(i=1; ; i++)
		{
			if(i==4)
			{
				_PROTECTED_WRITE(RSTCTRL_SWRR, RSTCTRL_SWRE_bm);
			}
			blink(i);
		}
    }
}

