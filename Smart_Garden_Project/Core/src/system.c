#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "system.h"
#include "config.h"

static bool init = false;
static bool drivers_and_data_initialized = false;

float first_read_temperature_celsius;
float first_read_light_procent;
float first_read_soil_moisture;
float first_read_water_level;

static void visual_init(void);

void drivers_init(void){
	init = true;
	visual_init();
	init = false;
	buttons_init();
	visual_init();
	
	ADC_init();
	visual_init();
	
	PWM_init(pump_port, pump_pin);
	visual_init();
	
	PWM_init(red_led_port, red_led_pin);
	visual_init();
	
	TIM_init();
	visual_init();
}

void peripherals_init(void){
	LightSensor_init(light_sensor_adc_channel,light_sensor_R_ref,light_sensor_V_ref);
	visual_init();
	
	LM35_init(temp_sensor_adc_channel,temp_sensor_V_ref);
	visual_init();
	
	console_init();
	visual_init();
	
	DDRH |= (1 << red_led_pin);
	visual_init();
	
	soil_sensor_init(soil_sensor_adc_channel, soil_sensor_V_ref);
	visual_init();
	
	water_sensor_init(water_sensor_adc_channel, water_sensor_V_ref);
	visual_init();
	
	drivers_and_data_initialized = true;
	visual_init();
	
	LCD_clear();
	
	sei();
}

void drivers_and_peripherals_init(void){
	drivers_init();
	peripherals_init();
}

void visual_init(void){
	if(init){
		I2C_init();
		LCD_init();
		
		LCD_gotoxy(1,0);
		LCD_print("Initialize....");
		LCD_gotoxy(0,1);
	}
	
	if(drivers_and_data_initialized){
		_delay_ms(10);
		first_read_temperature_celsius = read_LM35_Temp();
		LCD_sendData(0xFF);

		_delay_ms(10);
		first_read_light_procent = read_LightSensor_Percentages();	
		LCD_sendData(0xFF);
			
		first_read_soil_moisture = read_soil_sensor();
		LCD_sendData(0xFF);
		
		first_read_water_level = read_water_sensor();
		LCD_sendData(0xFF);
	}
	
	LCD_sendData(0xFF);
	_delay_ms(100);
}