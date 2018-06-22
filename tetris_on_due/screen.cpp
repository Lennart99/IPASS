#include "screen.hpp"

uint8_t screen::setPixel(unsigned int x, unsigned int y, bool b) {
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

void screen::setRow(unsigned int y, uint8_t d) {
	if(y > 0x07) y = 0x07;
	data[y] = d;
}

uint8_t screen::getRow(unsigned int y) {
	if(y > 0x07) y = 0x07;
	
	return data[y];
}