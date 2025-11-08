#include <avr/io.h>
#include "LCD_UI.h"
#include "LCD_TEST.h"
#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "Buttons.h"
#include "TIM.h"
	
enum LCD_MODES{
	MODE_NONE = 0,
	MODE_STANDBY,	//BackLight Off to save power
	MODE_ACTIVE
	};

static float UI_temperature_celsius;
static float UI_light_procent;
static float UI_soil_moisture = 0.0f;
static float UI_water_level = 0.0f;
static uint8_t UI_water_level_cycles = 0;
static uint8_t page_number = 0;
uint8_t length_of_floats = 0;
static uint32_t ui_timer;
	
static enum LCD_MODES current_mode = MODE_ACTIVE;

void LCD_UI_MainScreen(uint8_t page);

void LCD_UI_UpdateData(void){
	if(current_mode == MODE_ACTIVE ){
		if(ui_timer == 0){
			ui_timer = system_time_ms();
		}
		else if(system_time_ms() - ui_timer >= 30011){
			current_mode = MODE_STANDBY;
			ui_timer = system_time_ms();	
		}
		
		if(up_button_pressed){
			ui_timer = system_time_ms();
			if(page_number > 0){
				page_number--;
			}
			up_button_pressed = false;
		}
		if(down_button_pressed){
			ui_timer = system_time_ms();
			if(page_number < 3){
				page_number++;
			}
			else{
				page_number = 0;
			}	
			down_button_pressed = false;
		}
		LCD_UI_MainScreen(page_number);
	}
	
	if(current_mode == MODE_STANDBY){
		LCD_backlightOff();
		
		if(up_button_pressed || down_button_pressed || select_button_pressed){
			up_button_pressed = false;
			down_button_pressed = false;
			LCD_backlightOn();
			ui_timer = system_time_ms();
			current_mode = MODE_ACTIVE;
		}
	}
}

void LCD_UI_MainScreen(uint8_t page){
	char buffer[16];
	page_number = page;
	
	switch(page_number){
		case 0:
			LCD_gotoxy(0,0);
			LCD_print(" SMART  GARDEN ");
			LCD_gotoxy(15,0);
			LCD_print("^");
			
			LCD_gotoxy(15,1);
			LCD_print("v");
			LCD_gotoxy(0,1);
			LCD_print("---------------");
			
			break;
		case 1:
			length_of_floats = sprintf(buffer, "%.2f", UI_temperature_celsius);
			
			switch(length_of_floats){
				case 4:
					LCD_gotoxy(11,0);
					LCD_print("    ");
					break;
				case 5:
					LCD_gotoxy(12,0);
					LCD_print("   ");
					break;
				case 6:
					LCD_gotoxy(13,0);
					LCD_print("  ");
					break;
			}
	
			LCD_gotoxy(0,0);
			LCD_print("Temp:");
			LCD_print(buffer);
			LCD_sendData(degrees_char);
			LCD_print("C");
			LCD_gotoxy(15,0);
			LCD_print("^");
			
			length_of_floats = sprintf(buffer, "%.2f", UI_light_procent);
			
			switch(length_of_floats){
				case 4:
				LCD_gotoxy(11,1);
				LCD_print("    ");
				break;
				case 5:
				LCD_gotoxy(12,1);
				LCD_print("   ");
				break;
				case 6:
				LCD_gotoxy(13,1);
				LCD_print("  ");
				break;
			}
			LCD_gotoxy(11,1);
			LCD_print("    ");
			LCD_gotoxy(0,1);
			LCD_print("Light:");
			LCD_print(buffer);
			LCD_print("%");
			LCD_gotoxy(15,1);
			LCD_print("v");
			break;
			
		case 2:
			length_of_floats = sprintf(buffer, "%.2f", UI_soil_moisture);
		
			switch(length_of_floats){
				case 4:
				LCD_gotoxy(10,0);
				LCD_print("     ");
				break;
				case 5:
				LCD_gotoxy(11,0);
				LCD_print("    ");
				break;
				case 6:
				LCD_gotoxy(12,0);
				LCD_print("   ");
				break;
			}
			
			LCD_gotoxy(0,0);
			LCD_print("Soil:");
			LCD_print(buffer);
			LCD_print("%");
			LCD_gotoxy(15,0);
			LCD_print("^");
			
			length_of_floats = sprintf(buffer, "%.2f", UI_water_level);
			
			switch(length_of_floats){
				case 4:
				LCD_gotoxy(10,1);
				LCD_print("     ");
				break;
				case 5:
				LCD_gotoxy(11,1);
				LCD_print("    ");
				break;
				case 6:
				LCD_gotoxy(12,1);
				LCD_print("   ");
				break;
			}
			
			LCD_gotoxy(0,1);
			LCD_print("Water:");
			LCD_print(buffer);
			LCD_gotoxy(15,1);
			LCD_print("v");
			break;
			
		case 3:
			if (!select_button_pressed) {
				LCD_gotoxy(0,0);
				LCD_print("WATER THE PLANT");
				LCD_gotoxy(15,0);
				LCD_print("^");
				
				LCD_gotoxy(0,1);
				LCD_print(" -HOLD SELECT- ");
				
				LCD_gotoxy(15,1);
				LCD_print("v");
			}
			else if(select_button_pressed) {
				LCD_clear();
				LCD_gotoxy(0,0);
				LCD_print("WATERING...");
			}
			break;
	}
}

void set_mode(enum LCD_MODES mode) {
	current_mode = mode;
}

void UI_set_temperature(float temp_val){
	 UI_temperature_celsius = temp_val;
}

void UI_set_light_procent(float light_val){
	UI_light_procent = light_val;
}

void UI_set_soil_moisture(float soil_val){
	UI_soil_moisture = soil_val;
}

void UI_set_water_level(float water_val){
	UI_water_level = water_val;
}
