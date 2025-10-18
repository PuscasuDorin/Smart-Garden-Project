
#ifndef UART_H_
#define UART_H_

#define F_CPU 16000000UL

#include <stdbool.h>

extern volatile char rx_buffer[20];
extern volatile uint8_t rx_buffer_index;
extern volatile bool str_is_complete ;

void UART_Init(uint32_t baud_rate);

void UART_TransmitByte(uint8_t data);

void UART_TransmitString(char *string);

uint8_t UART_ReceiveByte(void);

#endif /* UART_H_ */