#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include "hwlib.hpp"

class screen {
private:
	uint8_t data[8] = {
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	};
	
public:
	screen()
		 {}

	uint8_t setPixel(unsigned int x, unsigned int y, bool b) {
		if(x > 0x07) x = 0x07;
		if(y > 0x07) y = 0x07;
		
		uint8_t d = data[y];
		if(b) {
			d = d | (0x80 >> x);
		} else {
			d = d & ~(0x80 >> x);
		}
		data[y] = d;

		return d;
	}
		
}; // class max7219

#endif // SCREEN_H