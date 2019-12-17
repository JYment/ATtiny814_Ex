/*
 * ExOSCCalib.c
 *
 * Created: 19-12-02 월 오후 05:00:56
 * Author : LABC
 */ 

/* 동작 
   PORTA.3에 연결된 LED 토글로 Hz 확인
*/


#define F_CPU	3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>


int main(void)
{
	uint8_t i;
	PORTA.DIRSET = _BV(3);
    while (1) 
    {
		// _PROTECTED_WRITE(CLKCTRL_OSC20MCALIBA, 0x1f);
		// MIN 0 ~ MAX 63
		_PROTECTED_WRITE(CLKCTRL_OSC20MCALIBA, 0);		// 약 12Mhz
		for(i=0; i<20; i++)
		{
			PORTA.OUTTGL = _BV(3);
			_delay_ms(100);
		}
		_delay_ms(1000);
		_PROTECTED_WRITE(CLKCTRL_OSC20MCALIBA, 0x1F);	// 약 20Mhz
		for(i=0; i<20; i++)
		{
			PORTA.OUTTGL = _BV(3);
			_delay_ms(100);
		}
		_delay_ms(1000);
		_PROTECTED_WRITE(CLKCTRL_OSC20MCALIBA, 0x3F);	// 약 30 Mhz
		for(i=0; i<20; i++)
		{
			PORTA.OUTTGL = _BV(3);
			_delay_ms(100);
		}
		_delay_ms(1000);
    }
}

