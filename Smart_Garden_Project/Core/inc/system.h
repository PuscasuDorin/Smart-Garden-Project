
#ifndef SYSTEM_H_
#define SYSTEM_H_

	//Drivers
	#include "ADC.h"
	#include "PWM.h"
	#include "TIM.h"
	#include "UART.h"

	//Peripherals
	#include "LightSensor.h"
	#include "LM35.h"
	#include "LCD_TEST.h"
	
	void Drivers_init(void);
	
	void Peripherals_init(void);

#endif /* SYSTEM_H_ */