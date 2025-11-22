#define F_CPU 16000000UL

#include <avr/io.h>
#include "WaterLevelSensor.h"
#include "ADC.h"
#include <util/delay.h>
#include "config.h"

static uint8_t water_sensor_channel = 0;
static float V_ref = 5.0f;

void water_sensor_init(uint8_t channel, float V_ref_param){
	DDRB |= (1 << water_sensor_pin);
	
	water_sensor_channel = channel;
	V_ref = V_ref_param;
	
	ADC_init();
}

float read_water_sensor(void){
	water_sensor_port |= (1 << water_sensor_pin);
	_delay_ms(10);
	float water_level = ADC_read_voltage(water_sensor_channel, V_ref);
	water_sensor_port &= ~(1 << water_sensor_pin);
	
	return water_level;
}