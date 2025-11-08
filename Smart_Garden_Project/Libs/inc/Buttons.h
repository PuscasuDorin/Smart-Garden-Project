

#ifndef BUTTONS_H_
#define BUTTONS_H_
	
	#include <stdbool.h>

	extern volatile bool up_button_pressed;
	extern volatile bool down_button_pressed;
	extern volatile bool select_button_pressed;

	void buttons_init(void);

#endif /* BUTTONS_H_ */