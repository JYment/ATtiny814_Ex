/*
 * ExCCL.c
 *
 * Created: 19-11-29 금 오후 03:51:42
 * Author : LABC
 */ 

#include <avr/io.h>
#include <avr/sfr_defs.h>

int main(void)
{
    PORTA.DIRSET	= _BV(7);
	
	TCA0.SINGLE.CTRLB	= TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_CMP1EN_bm | TCA_SINGLE_CMP2EN_bm;
	TCA0.SINGLE.CTRLA	= TCA_SINGLE_CLKSEL_DIV64_gc | TCA_SINGLE_ENABLE_bm;
	TCA0.SINGLE.CMP0	= 0x4000;
	TCA0.SINGLE.CMP1	= 0x8000;
	TCA0.SINGLE.CMP2	= 0xC000;
	
	CCL.LUT1CTRLC	= CCL_INSEL2_TCA0_gc;
	CCL.LUT1CTRLB	= CCL_INSEL1_TCA0_gc | CCL_INSEL0_TCA0_gc;
	CCL.TRUTH1	= 9;
	CCL.LUT1CTRLA	= CCL_OUTEN_bm | CCL_ENABLE_bm;
	CCL.CTRLA	= CCL_ENABLE_bm;
	
    while (1) 
    {
    }
}
