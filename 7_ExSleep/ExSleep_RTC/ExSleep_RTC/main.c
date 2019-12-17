/*
 * ExSleep_RTC.c
 *
 * Created: 19-11-29 금 오전 10:19:56
 * Author : LABC
 */ 

/*
	작동원리:
	_delay_ms(T) 는 CPU가 열심히 연산을 하면서 Tms를 대기하는 것이다.
	이것을 보완해서 Tms동안 sleep로 대기하는 함수를 만들었다.
	시간을 측정해야 하므로 RTC 타이머를 사용했는데 다른 타이머를 써도 된다.
*/

#define F_CPU	3333333UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>


ISR(RTC_CNT_vect)
{
	RTC.INTFLAGS	= RTC_OVF_bm;
}


void delay_ms_sleep_rtc(uint16_t t_ms)
{
	uint8_t ps;
	asm("in __tmp_reg__, __SREG__");
	asm("sei");
	asm("push __tmp_reg__");
	
	for ( ps=0; t_ms >= 2000; ps++){
		t_ms = t_ms >> 1;
	}
	
	while (RTC.STATUS > 0);		// Wait for all register to be synchronized
	
	RTC.CNT	= 0x0;
	RTC.PER	= (uint16_t) (t_ms * 32.768);
	RTC.INTCTRL	= RTC_OVF_bm;
//	RTC.CTRLA= RTC_RTCEN_bm;
	RTC.CTRLA	= RTC_RUNSTDBY_bm | RTC_RTCEN_bm;
	
//	set_sleep_mode(SLEEP_MODE_IDLE);
	set_sleep_mode(SLEEP_MODE_STANDBY);
//	set_sleep_mode(SLEEP_MODE_PWR_DOWN);	
	sleep_enable();
	
	sleep_cpu();
	// 이 위치에서 대부분의 시간을 소비
	sleep_disable();
	
	RTC.CTRLA &= ~RTC_RTCEN_bm;

    asm("pop __tmp_reg__");
    asm("out __SREG__, __tmp_reg__");
}


int main(void)
{
    PORTA.DIRSET	= _BV(3);
	
    while (1) 
    {
		for(int i=0; ;i++)
		{
			PORTA.OUTSET	= _BV(3);
			delay_ms_sleep_rtc(100 + (i&7)*100);
			PORTA.OUTCLR	= _BV(3);
			delay_ms_sleep_rtc(100 + (i&7)*100);
		}
    }
}

