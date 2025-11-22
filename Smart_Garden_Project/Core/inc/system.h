
#ifndef SYSTEM_H_
#define SYSTEM_H_

	#include "console.h"
	
	//Drivers
	#include "ADC.h"
	#include "PWM.h"
	#include "TIM.h"
	#include "UART.h"
	#include "Buttons.h"

	//Peripherals
	#include "LightSensor.h"
	#include "LM35.h"
	#include "LCD_TEST.h"
	
	extern float first_read_temperature_celsius;
	extern float first_read_light_procent;
	extern float first_read_soil_moisture;
	extern float first_read_water_level;
	
	void drivers_init(void);
	
	void peripherals_init(void);
	
	void drivers_and_peripherals_init(void);

#endif /* SYSTEM_H_ */