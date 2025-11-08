#include <avr/io.h>
#include "LCD_UI.h"
#include "LCD_TEST.h"
#include <stdio.h>
	
enum LCD_MODES{
	MODE_NONE = 0,
	MODE_STANDBY,	//BackLight Off to save power
	MODE_ACTIVE
	};

static float UI_temperature_celsius = 0.0f;
static float UI_light_procent = 0.0f;
static float UI_soil_moisture = 0.0f;
static float UI_water_level = 0.0f;
static uint8_t UI_water_level_cycles = 0;
static uint8_t page_number = 0;
	
static enum LCD_MODES current_mode = MODE_NONE;

void LCD_UI_init(void){
	
}

void LCD_UI_UpdateData(void){
	
}

void LCD_UI_MainScreen(uint8_t page){
	char buffer[16];
	page_number = page;
	switch(page_number){
		case 0:
			LCD_gotoxy(12,0);
			LCD_print(" ");
			LCD_gotoxy(0,0);
			LCD_print("Temp:");
			sprintf(buffer, "%.2f", UI_temperature_celsius);
			LCD_print(buffer);
			LCD_sendData(degrees_char);
			LCD_print("C");
			LCD_gotoxy(15,0);
			LCD_print("^");
			
			LCD_gotoxy(12,0);
			LCD_print(" ");
			LCD_gotoxy(0,1);
			LCD_print("Light:");
			sprintf(buffer, "%.2f", UI_light_procent);
			LCD_print(buffer);
			LCD_print("%");
			LCD_gotoxy(15,1);
			LCD_print("v");
			break;
			
		case 1:
			LCD_gotoxy(10,0);
			LCD_print("  ");
			LCD_gotoxy(0,0);
			LCD_print("Soil:");
			sprintf(buffer, "%.2f", UI_soil_moisture);
			LCD_print(buffer);
			LCD_print("%");
			LCD_gotoxy(15,0);
			LCD_print("^");
			
			LCD_gotoxy(10,0);
			LCD_print("  ");
			LCD_gotoxy(0,1);
			LCD_print("Water:");
			sprintf(buffer, "%.2f", UI_water_level);
			LCD_print(buffer);
			LCD_gotoxy(15,1);
			LCD_print("v");
			break;
			
		case 3:
			LCD_gotoxy(0,0);
			LCD_print("WATER THE PLANT");
			LCD_gotoxy(15,0);
			LCD_print("^");
			
			LCD_gotoxy(1,1);
			LCD_print("-HOLD BUTTON-");
			
			LCD_gotoxy(15,1);
			LCD_print("v");
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
