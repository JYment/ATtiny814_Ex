/*
 * usart_poll.h
 *
 * Created: 19-11-28 목 오후 05:01:47
 *  Author: LABC
 */ 


#ifndef USART_POLL_H_
#define USART_POLL_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif	

#define USART0_BAUD_RATE(BAUD_RATE)		((float) (F_CPU * 64 / (16 * (float)BAUD_RATE)))
//#define USART0_BAUD_RATE(BAUD_RATE)		((float) (F_CPU * 64 / (16 * (float)BAUD_RATE)) * 0.5)

int8_t USART_0_init();
void USART_0_enable();
void USART_0_enable_rx();
void USART_0_enable_tx();
void USART_0_disable();
uint8_t USART_0_get_data();
bool USART_0_is_rx_ready();
bool USART_0_is_tx_ready();
bool USART_0_is_tx_busy();
uint8_t USART_0_ready();
void USART_0_write(const uint8_t data);
int usart_poll_test();

#ifdef __cplusplus
}
#endif



#endif /* USART_POLL_H_ */