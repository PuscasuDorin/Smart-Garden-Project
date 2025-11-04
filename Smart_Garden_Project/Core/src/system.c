#include <avr/io.h>
#include "system.h"

//Drivers
#include "ADC.h"
#include "PWM.h"
#include "TIM.h"
#include "UART.h"

//Peripherals
#include "LightSensor.h"
#include "LM35.h"

void Drivers_init(void){
	ADC_init();
	PWM_init(pump_port, pump_pin);
	TIM_init();
	UART_Init(UART_baud_rate);
}

void Peripherals_init(void){
	LightSensor_init(light_sensor_adc_channel,light_sensor_R_ref,light_sensor_V_ref);
	
	LM35_init(temp_sensor_adc_channel,temp_sensor_V_ref);
}