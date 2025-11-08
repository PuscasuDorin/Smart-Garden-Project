
#ifndef CONFIG_H_
#define CONFIG_H_
	
	#define F_CPU 16000000UL
	
	#define full_block_char 0xFF
	#define degrees_char 0xDF

	#define pump_port &PORTE
	#define pump_pin PE4
	
	#define UART_baud_rate 9600
	
	#define light_sensor_adc_channel 1
	#define light_sensor_R_ref 9800
	#define light_sensor_V_ref 5.0f
	
	#define temp_sensor_adc_channel 0
	#define temp_sensor_V_ref 5.0f
	
	#define rgb_r_port &PORTH
	#define rgb_r_pin PH3
	#define rgb_g_port &PORTH
	#define rgb_g_pin PH4
	#define rgb_b_port &PORTH
	#define rgb_b_pin PH5
	
	#define up_b_port &PORTB
	#define up_b_pin PB0
	#define down_b_port &PORTB
	#define down_b_pin PB1
	#define start_b_port &PORTB
	#define start_b_pin PB2

#endif /* CONFIG_H_ */