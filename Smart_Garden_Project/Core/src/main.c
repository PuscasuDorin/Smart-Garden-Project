/*
 * Smart_Garden_Project.c
 *
 * Created: 10/17/2025 3:11:53 PM
 * Author : Dorin
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "system.h"
#include <avr/interrupt.h>

int main(void)
{
	Peripherals_init();
	Drivers_init();
	
    while (1) 
    {
		uint32_t global_time = TIM_value();
		if(global_time % 1000 == 0){
		char strr[10];
		sprintf(strr, "%lu", global_time);
		UART_TransmitString(strr);
		UART_TransmitString("\n\r");
		}
		
		
	/*	
		float number =  read_LM35_Temp();
		char str[6];
		
		sprintf(str, "%.2f", number);
		UART_TransmitString("Temp:");
		UART_TransmitString(str);
		UART_TransmitByte('\n');
		UART_TransmitByte('\r');
		LCD_gotoxy(0,0);
		LCD_print("Temp:");
		LCD_print(str);	
	
	
		float num =  read_LightSensor_Percentages();
		char strr[6];
		sprintf(strr, "%.2f", num);
		UART_TransmitString("Light:");
		UART_TransmitString(strr);
		UART_TransmitByte('\n');
		UART_TransmitByte('\r');
		//LCD_gotoxy(0,1);
		//LCD_print("Light:");
		//LCD_print(strr);
		_delay_ms(1000);
		//LCD_clear();
		
		//_delay_ms(1000);
		
		*/
		
    }
}