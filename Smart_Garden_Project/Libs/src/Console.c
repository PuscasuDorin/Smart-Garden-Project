#include <avr/io.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "console.h"
#include "config.h"
#include "LCD_TEST.h"
#include "system.h"
#include <avr/interrupt.h>
#include <stdio.h>

enum CONSOLE_MODES{
	MODE_NONE = 1,
	MODE_UI,
	MODE_SENSORS,
	MODE_ACTUATORS,
	MODE_COMPONENT_PINS
};

static void set_mode(enum CONSOLE_MODES mode);
static void UI_mode(void);
static void Sensors_mode(void);
static void Actuators_mode(void);
static void lcd_test_mode(void);
//static void rgb_led_test_mode(void);

volatile bool debugging = false;
static enum CONSOLE_MODES current_mode = MODE_NONE;

void console_init(void){
	UART_Init(UART_baud_rate);
	UART_TransmitString("=== Smart Garden Console ===\n\r");
	UART_TransmitString("Type 'help' to view commands.\n\r");
	//if user typed help then 
	//LCD_gotoxy(0,0);
	//LCD_print("-DEBUGGING MODE-");
	//LCD_gotoxy(0,1);
	//LCD_print("----------------");
	//UI_mode();
}

void start_debugging(void){
	return;
	UART_TransmitString("See Sensors Pins and Ports");
}

void set_mode(enum CONSOLE_MODES mode) {
	current_mode = mode;
	
	switch(mode) {
		case 1:
			UART_TransmitString("=== Console inactive ===\n\r");
			break;
		case 2:
			UART_TransmitString("=== UI test mode active ===\n\r");
			break;
		case 3:
			UART_TransmitString("=== Sensors test mode active ===\n\r");
			break;
		case 4:
			UART_TransmitString("=== Actuators test mode active ===\n\r");
			break;
		case 5:
			UART_TransmitString("=== Display Component Pins ===\n\r");
			break;
	}
}

void UI_mode(void){
	while(1){
		uint8_t ui_selection;
		bool ui_selected = false;
		
		UART_TransmitString("What do you want to test? \n\r");
		UART_TransmitString("1. LCD_TEST \n\r");
		UART_TransmitString("2. RGB_LED_TEST \n\r");
		UART_TransmitString("3. BACK \n\r");
		
		while (!ui_selected){
			while(!str_is_complete);
			if(str_is_complete){
				str_is_complete = false;
		
				if(strcmp((const char *)rx_buffer, "1") == 0){
					ui_selection = 1;
					ui_selected = true;
				}
				else if(strcmp((const char *)rx_buffer, "2") == 0){
					ui_selection = 2;
					ui_selected = true;
				}
				else if(strcmp((const char *)rx_buffer, "3") == 0){
					return;
				}
				else{
					UART_TransmitString("Invalid selection! Try again! \n\r");
				}
			}
		}
		switch(ui_selection) {
			case 1:
				UART_TransmitString("=== LCD_TEST selected ===  \n\r");
				LCD_clear();
				lcd_test_mode();
				break;
			case 2:
				UART_TransmitString("=== RGB_LED_TEST selected ===  \n\r");
				rgb_led_test_mode();
				break;
		}
	}
}

void Sensors_mode(void){
	uint8_t value = 0;
	UART_TransmitString("What do you want to do? \n\r");
	UART_TransmitString("1. Take readings \n\r");
	UART_TransmitString("2. BACK \n\r");
	
	UART_TransmitString("How many sensor readings do you want to take?\n\r");
	UART_TransmitString(">> ");
	while(!str_is_complete);
	
	if(str_is_complete){
		str_is_complete = false;
		
		value = atoi((const char *)rx_buffer);
		
		char buffer[16];
		for(int i = 1; i <= value; i++){
			UART_TransmitString("=== Reading ");
			sprintf(buffer, "%d", i);
			UART_TransmitString(buffer);
			UART_TransmitString(" === \n\r");
			
			UART_TransmitString(">> Temperature: ");
			sprintf(buffer, "%.2f", read_LM35_Temp());
			UART_TransmitString(buffer);
			
			UART_TransmitString(">> Luminosity: ");
			sprintf(buffer, "%.2f", read_LightSensor_Percentages());
			UART_TransmitString(buffer);
			UART_TransmitString("% \n\r");
			
			UART_TransmitString(">> Soil Moisture: ");
			UART_TransmitString("\n\r");
			//
			
			UART_TransmitString(">> Water Level: ");
			UART_TransmitString("\n\r");
			//
			_delay_ms(1000);
		}
	}
	
}

void Actuators_mode(void){
	return;
}

void Component_Pins_mode(void){
	return;
}

void lcd_test_mode(void){
	bool row_selected = false;
	
	while(!row_selected){
		UART_TransmitString("LCD_TEST >> Enter the row number(0 or 1): ");
		
		while(!str_is_complete);
		
		if(str_is_complete){
			str_is_complete = false;
			
			if(strcmp((const char *)rx_buffer, "0") == 0){
				LCD_gotoxy(0,0);
				row_selected = true;
			}
			else if(strcmp((const char *)rx_buffer,"1") == 0){
				LCD_gotoxy(0,1);
				row_selected = true;
			}
			else{
				UART_TransmitString("LCD_TEST >> Invalid row! Must be 0 or 1. \n\r");
			}
		}
	}
	
	UART_TransmitString("\n\r");
	UART_TransmitString("LCD_TEST >> Type the text(max 8 chars): ");
	
	while(!str_is_complete);
	
	if(str_is_complete){
		str_is_complete = false;
		
		char lcd_temp_buffer[17];
		cli();
		strncpy(lcd_temp_buffer,(const char *)rx_buffer, 17);
		
		LCD_print(lcd_temp_buffer);
		sei();
		UART_TransmitString("LCD_TEST >> Text written to LCD!\n\r");
	}
}

/*
void rgb_led_test_mode(void){
	uint8_t value = 0;
	bool red_intensity_selected = false;
	bool green_intensity_selected = false;
	bool blue_intensity_selected = false;
	
	while (!red_intensity_selected){
		UART_TransmitString("RGB_LED_TEST >> Red LED intensity (0-255): ");

		while(!str_is_complete);
		if(str_is_complete){
			str_is_complete = false;
			
			value = atoi((const char *)rx_buffer);
			if(value >= 0 && value <= 255){
				set_LED_Brightness(rgb_r_port, rgb_r_pin, value);
				red_intensity_selected = true;
			}
			else{
				UART_TransmitString("RGB_LED_TEST >> Invalid value! Try again! /n/r");
			}
		}
	}
	
	while (!green_intensity_selected){
		UART_TransmitString("RGB_LED_TEST >> Green LED intensity (0-255): ");

		while(!str_is_complete);
		if(str_is_complete){
			str_is_complete = false;
			
			value = atoi((const char *)rx_buffer);
			if(value >= 0 && value <= 255){
				set_LED_Brightness(rgb_g_port, rgb_g_pin, value);
				green_intensity_selected = true;
			}
			else{
				UART_TransmitString("RGB_LED_TEST >> Invalid value! Try again! /n/r");
			}
		}
	}
	
	while (!blue_intensity_selected){
		UART_TransmitString("RGB_LED_TEST >> Blue LED intensity (0-255): ");

		while(!str_is_complete);
		if(str_is_complete){
			str_is_complete = false;
			
			value = atoi((const char *)rx_buffer);
			if(value >= 0 && value <= 255){
				set_LED_Brightness(rgb_b_port, rgb_b_pin, value);
				blue_intensity_selected = true;
			}
			else{
				UART_TransmitString("RGB_LED_TEST >> Invalid value! Try again! /n/r");
			}
		}
	}
} */