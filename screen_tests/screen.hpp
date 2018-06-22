#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

class screen {
private:
	uint8_t data[8] = {
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	};
	
public:
	screen()
		 {}

	uint8_t setPixel(unsigned int x, unsigned int y, bool b);
		
}; // class max7219

#endif // SCREEN_H