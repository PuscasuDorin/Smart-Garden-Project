
#ifndef PWM_H_
#define PWM_H_
	
	#include <stdbool.h>

	void PWM_init (volatile uint8_t *pwm_port,uint8_t pwm_pin);
	
	void set_PumpSpeed(volatile uint8_t *pwm_port, uint8_t set_pumpPin, uint8_t speed);
	
	void set_LED_Brightness(volatile uint8_t *pwm_port, uint8_t set_ledPin, uint8_t brightness);
	
	
#endif /* PWM_H_ */