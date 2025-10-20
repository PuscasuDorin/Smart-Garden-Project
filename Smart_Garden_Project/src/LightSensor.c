#include <avr/io.h>
#include "LightSensor.h"
#include "ADC.h"

static uint8_t ADC_channel = 0;
static uint32_t R_val = 10 * 1000;
static float V_ref_val = 3.3f;

void LightSensor_init(uint8_t ADC_channel_param, uint32_t R_val_param, float V_ref_val_param){
	ADC_channel = ADC_channel_param;
	R_val = R_val_param;
	V_ref_val = V_ref_val_param;
	
	ADC_init();
}

uint32_t read_LightSensor(void){
	float adc_val = ADC_read_voltage(ADC_channel, V_ref_val);
	
	if (adc_val < 0.001f){
		 return 0;
	}
	else{
		uint32_t sensor_val = (R_val*(V_ref_val-adc_val))/adc_val;
		return (sensor_val);
	}
}