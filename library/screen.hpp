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
	
	void setRow(unsigned int y, uint8_t data);
	
	uint8_t getRow(unsigned int y);
		
}; // class screen

#endif // SCREEN_H