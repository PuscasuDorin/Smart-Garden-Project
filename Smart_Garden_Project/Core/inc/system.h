
#ifndef SYSTEM_H_
#define SYSTEM_H_

//Add functions initialization
	#define pump_port &PORTE
	#define pump_pin PE4
	#define UART_baud_rate 9600
	#define light_sensor_adc_channel 0
	#define light_sensor_R_ref 9800
	#define light_sensor_V_ref 5.0f
	#define temp_sensor_adc_channel 1
	#define temp_sensor_V_ref 5.0f
	
	void Drivers_init(void);
	
	void Peripherals_init(void);

#endif /* SYSTEM_H_ */