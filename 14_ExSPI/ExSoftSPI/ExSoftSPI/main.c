/*
 * ExSoftSPI.c
 *
 * Created: 19-12-12 목 오후 05:18:29
 * Author : LABC
 */ 

/*  attiny 1-series SW로 구현한 SPI
 
	연결
	Master                            Slave
	A1 MOSI------------------------>MOSI A1
	A2 MISO<------------------------MISO A2
	A3 SCK ------------------------>SCK  A3
	A6 SS_ -------------------------SS_  A0 (tiny412)
	A7 --LED>]--(1k)--GND--(1k)--[<LED]-- A7
	** tiny814,817등에서는 SS_를 아래와 같이 구성하고 #define SS_ _BV(4)로 설정
	A4 SS_ -------------------------SS_  A4 (tiny814,tiny817)
 
 
	#define MASTER      1   ---- master로 컴파일
	#define MASTER      0   ---- slave로  컴파일
 
	ㅇ작동 : slave를 먼저 실행하고 master을 나중 실행한다(master 함수에 300ms 지연함수 포함)
	1.master("ABCD")<-->slave("abcd") 서로 교환한다.
	2.master<-->slave 서로 받은 값을 교환한다.
	성공하면 LED가 켜지고,
	실패하면 LED가 점멸한다
 
	SPI mode1으로 작동
 	PORT A0는 UPDI 모드에서도 디지털 out외의 GPIO input, interrupt 기능 등은 동작하므로 퓨즈는 수정할 필요가 없다.
*/


#define MASTER		1
#define F_CPU		3333333UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define MOSI		_BV(1)
#define MISO		_BV(2)
#define SCK			_BV(3)


#if MASTER==1
#define SS_			_BV(4)		// Tiny412 : MASTER=6, SLAVE=0, TINY814 : MASTER=4
#else
#define SS_			_BV(0)
#endif

// tx 최소가능 펄스 간격은 3+3us이지만
// rx 최소가능 펄스 간격이 5+5us 인점을 감안하면 PULSE_US > 12
// SPI 프리스케일러는 64(10+10us) 또는 128(20+20us) 가 가능함
#define PULSE_US        (10-3)
// mode=1 DORD=0

void spi_init(uint8_t master)
{
	if(master)
	{
		PORTA.DIRCLR = MISO;
		PORTA.OUTSET = SS_;
		PORTA.DIRSET = MOSI | SCK | SS_;
	}
	else
	{
		PORTA.DIRSET = MISO;
		PORTA.DIRCLR = MOSI | SCK | SS_;
	}
}

// master spi 함수
void spi_tx(uint8_t *c)
{
	uint8_t i, d;
	d = *c;
	*c = 0;
	_delay_us(PULSE_US);
	
	for(i=0; i<8; i++)
	{
		PORTA.OUTSET = SCK;
		if((d&0x80) == 0)
		{
			PORTA.OUTCLR = MOSI;
		}
		else
		{
			PORTA.OUTSET = MOSI;
		}
		d <<= 1;
		*c <<= 1;
		_delay_us(PULSE_US);
		PORTA.OUTCLR = SCK;
		if((PORTA.IN & MISO) != 0)
		{
			*c |= 1;
		}
		_delay_us(PULSE_US);
	}	
	_delay_us(PULSE_US);
}

// SLAVE SPI 함수
void spi_rx(uint8_t *c)
{
	uint8_t i, d;
	
	d = *c;
	while((PORTA.IN & SS_) != 0);
	*c = 0;
	for(i=0; i<8; i++)
	{
		while((PORTA.IN & SCK) == 0);
		if((d & 0x80) == 0)
		{
			PORTA.OUTCLR = MISO;
		}
		else
		{
			PORTA.OUTSET = MISO;
		}
		d <<= 1;
		*c <<= 1;
		while((PORTA.IN & SCK) != 0);
		if((PORTA.IN & MOSI) != 0)
		{
			*c |= 1;
		}
	}
}



int main(void)
{
	uint8_t i, buf[8], check = 0;
	

#if MASTER==1	
    spi_init(1);		// MASTER
	_delay_ms(300);		// MASTER, SLAVE 동시에 켰을 때 MASTER가 늦게 시작하게 하기 위함
	
	strcpy((char *) buf, "ABCD");
	PORTA.OUTCLR = SS_;
	for(i=0; i<4; i++)
	{
		spi_tx(&buf[i]);		// ABCD <---> abcd
	}
	PORTA.OUTSET = SS_;
	
	if(strncmp((char *)buf, "abcd", 4) == 0)
	{
		check = 1;
	}
	_delay_ms(10);		// SLAVE에게 시간을 주기 위함
	PORTA.OUTCLR = SS_;
	
	for(i=0; i<4; i++)
	{
		spi_tx(&buf[i]);
	}
	PORTA.OUTSET = SS_;
	
	if(strncmp((char *)buf, "ABCD", 4) == 0)
	{
		check |= 2;
	}
	PORTA.DIRCLR = SS_;
#else
	spi_init(0);		// SLAVE
	
	strcpy((char *) buf, "abcd");
	for (i = 0; i < 4; i++)
	{
		spi_rx(&buf[i]);
	}
	while( ((PORTA.IN&SS_)==0) );
	 
	if ( strncmp((char *)buf, "ABCD", 4)==0 ) check = 1;
	
	for (i = 0; i < 4; i++)
	spi_rx(&buf[i]);
	while( ((PORTA.IN&SS_)==0) );
	 
	if ( strncmp((char *)buf, "abcd", 4)==0 ) check |= 2;
#endif
	 
	PORTA.DIRSET = _BV(7);
	PORTA.OUTSET = _BV(7);
	while(1)
	{
		if(check != 3)
		{
			PORTA.OUTTGL = _BV(7);
		}
		_delay_ms(250);
	}
}

