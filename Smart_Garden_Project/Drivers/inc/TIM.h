
#ifndef TIM_H_
#define TIM_H_

	void TIM_init(void);

	uint32_t system_time_ms(void);
	
	uint32_t ms_counter(void);
	
	void stop_ms_counter(void);

#endif /* TIM_H_ */