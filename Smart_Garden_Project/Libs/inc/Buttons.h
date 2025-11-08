

#ifndef BUTTONS_H_
#define BUTTONS_H_
	
	#include <stdbool.h>

	extern volatile bool button_up_pressed;
	extern volatile bool button_down_pressed;
	extern volatile bool button_start_pressed;

	void buttons_init(void);

#endif /* BUTTONS_H_ */