/*
 * sw_uart.c
 *
 * Created: 19-11-28 목 오후 04:40:17
 *  Author: LABC
 */ 

#include "sw_uart.h"

#define USE_PRINTF
#ifdef USE_PRINTF
#if defined(__GNUC__)
int UART_SW_printCHAR(char ch, FILE *stream)
{
	putch(ch);
	return 0;
}


FILE UART_SW_stream = FDEV_SETUP_STREAM(UART_SW_printCHAR, NULL, _FDEV_SETUP_WRITE);

#elif defined(__ICCAVR__)

int putchar(int outChar)
{
	putch(outChar);
	return outChar;
}
#endif
#endif

#define BIT_USEC		((1000000UL+BAUD_RATE/2-50000)/BAUD_RATE)

static struct sw_uart_type{
	volatile uint8_t *port;
	uint8_t pin_bp;
	uint8_t pin_bm;
}uart_tx, uart_rx;


void init_uart(volatile uint8_t *port, uint8_t pin_bp, int8_t tx)
{
	if(tx)
	{
		uart_tx.port		= port;
		uart_tx.pin_bp		= pin_bp;
		uart_tx.pin_bm		= _BV(pin_bp);
		*(port + 1)			= _BV(pin_bp);		// DIRSET
		*(port + 5)			= _BV(pin_bp);		// OUTSET
	}
	else
	{
		uart_rx.port		= port;
		uart_rx.pin_bp		= pin_bp;
		uart_rx.pin_bm		= _BV(pin_bp);
		*(port + 2)			= _BV(pin_bp);		// DIRCLR
		*(port + 0x10 + pin_bp)		|= PORT_PULLUPEN_bm;		// PINCTRLn
	}
	
	#ifdef USE_PRINTF
	#if defined(__GNUC__)
	stdout = &UART_SW_stream;
	#endif
	#endif
}

int16_t getch(void)
{
	uint8_t i, c;
	
	if((*(uart_rx.port + 8) & uart_rx.pin_bm) != 0)		return -1;		// 신호가 없음
	_delay_us(BIT_USEC + BIT_USEC/2);
	
	c = 0;
	for(i=0; i<8; i++)
	{
		c >>= 1;
		if((*(uart_rx.port + 8) & uart_rx.pin_bm) != 0)		c |= 0x80;
		_delay_us(BIT_USEC);
	}
	
	if((*(uart_rx.port + 8) & uart_rx.pin_bm) == 0)		return -1;		// 스탑비트가 없음
	// 스탑비트가 끝나길 기다리지 않는 것이 맞다
	// 끝날 때까지 기다리면 다음 입력 받기에 차질이 생길 수 있다
	// _delay_us(BIT_USEC/2);
	
	return (int16_t) c;
}


void putch(int16_t c)
{
	for(c=(c<<1)|512; c!=0; c=c>>1)
	{
		if(c&1)		*(uart_tx.port + 5) = uart_tx.pin_bm;
		else		*(uart_tx.port + 6) = uart_tx.pin_bm;
		_delay_us(BIT_USEC);
	}
}


static char _hex(char i)
{
	if(i > 9)	return 'A' + (i-10);
	return '0' + i;
}

void puth(uint8_t c)
{
	putch(_hex(c >> 4));
	putch(_hex(c & 15));
}

void putb(uint8_t c)
{
	uint8_t i;
	for(i=0x80; i != 0; i=i>>1)
	{
		if((c&i)==0)	putch('0');
		else			putch('1');
	}
}

static void _puti(int16_t i)
{
	if(i == 0)	return;
	_puti(i / 10);
	putch('0' + i % 10);
}

void puti(int16_t i)
{
	if(i < 0)
	{
		putch('-');
		i= -i;
	}
	if(i == 0)	putch('0');
	_puti(i);
}


void putstr(char *s)
{
	while(*s)	putch(*s++);
}

void putcr(void)
{
	putch('\r');
	putch('\n');
}