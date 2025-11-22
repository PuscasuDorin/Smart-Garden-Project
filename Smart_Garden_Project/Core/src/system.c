#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "system.h"
#include "config.h"

static bool init = false;
static bool drivers_and_data_initialized = false;

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
	
	DDRB |= (1 << water_sensor_pin) | (1 << soil_sensor_pin);
	DDRH |= (1 << red_led_pin);
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
		I2C_Init();
		LCD_init();
		
		LCD_gotoxy(1,0);
		LCD_print("Initialize....");
		LCD_gotoxy(0,1);
	}
	
	if(drivers_and_data_initialized){
		for (int i = 0; i < 5; i++){
			read_LightSensor_Percentages();
			_delay_ms(10);
		}
		
		for (int i = 0; i < 5; i++){
			read_LM35_Temp();
			_delay_ms(10);
		}
		
		for (int i = 0; i < 5; i++){
			ADC_read_voltage(soil_sensor_adc_channel, soil_sensor_V_ref);
			_delay_ms(10);
		}
		
		for (int i = 0; i < 5; i++){
			ADC_read_voltage(water_sensor_adc_channel, water_sensor_V_ref);
			_delay_ms(10);
		}
		LCD_sendData(0xFF);
		
		LCD_sendData(0xFF);
		LCD_sendData(0xFF);
		LCD_sendData(0xFF);
		LCD_sendData(0xFF);
	}
	
	LCD_sendData(0xFF);
	_delay_ms(100);
}