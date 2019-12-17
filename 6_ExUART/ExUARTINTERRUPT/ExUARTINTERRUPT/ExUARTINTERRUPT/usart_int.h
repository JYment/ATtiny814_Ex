/*
 * usart_int.h
 *
 * Created: 19-11-29 금 오전 10:08:28
 *  Author: LABC
 */ 


#ifndef USART_INT_H_
#define USART_INT_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

#define USART_0_RX_BUFFER_SIZE 8
#define USART_0_TX_BUFFER_SIZE 8
#define USART_0_RX_BUFFER_MASK (USART_0_RX_BUFFER_SIZE - 1)
#define USART_0_TX_BUFFER_MASK (USART_0_TX_BUFFER_SIZE - 1)

typedef enum { RX_CB = 1, UDRE_CB } usart_cb_type_t;
typedef void (*usart_cb_t)(void);

int8_t USART_0_init();
void USART_0_enable();
void USART_0_enable_rx();
void USART_0_enable_tx();
void USART_0_disable();
uint8_t USART_0_get_data();
bool USART_0_is_tx_ready();
bool USART_0_is_rx_ready();
bool USART_0_is_tx_busy();
uint8_t USART_0_read(void);
void USART_0_write(const uint8_t data);
void USART_0_set_ISR_cb(usart_cb_t cb, usart_cb_type_t type);
int usart_test();

#ifdef __cplusplus
}
#endif

#endif /* USART_INT_H_ */
