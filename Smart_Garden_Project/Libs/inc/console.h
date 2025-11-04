
#ifndef CONSOLE_H_
#define CONSOLE_H_

	#include <stdbool.h>

	extern volatile bool debugging;
	
	void console_init(void);
	
	void start_debugging(void);



#endif /* CONSOLE_H_ */