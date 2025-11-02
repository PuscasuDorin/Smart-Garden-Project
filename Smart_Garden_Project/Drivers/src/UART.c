#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <UART.h>

volatile char rx_buffer [20];
volatile uint8_t rx_buffer_index = 0;
volatile bool str_is_complete = false;

void UART_Init(uint32_t baud_rate){
	uint16_t ubrr = (F_CPU / (16 * baud_rate) -1);
	
	UBRR0H = (uint8_t)(ubrr>>8);
	UBRR0L = (uint8_t)(ubrr);
	
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) |  (1 << RXCIE0);

	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
}

void UART_TransmitByte(uint8_t data){
	while (!(UCSR0A & (1<<UDRE0)));
	 
	UDR0 = data;
}

void UART_TransmitString(char *string){
	while(*string){
		UART_TransmitByte(*string++);
	}
}

uint8_t UART_ReceiveByte(void){
	while (!(UCSR0A & (1<<RXC0)));
	
	return UDR0;
}

ISR(USART0_RX_vect){
	
	char character = UDR0;
	if (character == '\n' || character == '\r'){
				
		rx_buffer[rx_buffer_index] = '\0';
		rx_buffer_index = 0;
		str_is_complete = true;
	}
	else if (rx_buffer_index < sizeof(rx_buffer)-1){
	
		rx_buffer [rx_buffer_index] = character;
		rx_buffer_index++;
	}
	

	
}