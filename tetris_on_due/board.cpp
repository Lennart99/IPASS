#include "board.hpp"

uint16_t board::getRow(unsigned int y) {
	uint8_t * point = window.getRow(y);
	
	uint16_t res = *point;
	res = (res << 8) & 0xFF00;
	res = res | (*(point+1) & 0x00FF);
	
	return res;
}

void board::setRow(unsigned int y, uint16_t d) {
	if(y > 23) y = 23;
	
	uint8_t out[2];
	out[0] = (d >> 8) & 0xFF;
	out[1] = d & 0xFF;
	
	window.setRow(y,out);
}

bool board::getPixel(unsigned int y, unsigned int x) {
	uint16_t d = getRow(y);
	uint16_t mask = 0x8000 >> x;
	d = d & mask;
	return d == mask;
}

void board::setPixel(unsigned int y, unsigned int x, bool b) {
	uint16_t d = getRow(y);
	if(b) {
		d = d | (0x8000 >> x);
	} else {
		d = d & ~(0x8000 >> x);
	}
	setRow(y,d);
}

void board::removeFullRows() {
	for(unsigned int y = 0; y < 24; y++) {
		// remove all rows that are directly on top of the first one
		while(getRow(y) == 0xFFFF) {
			// shift everything down by one
			for(unsigned int i = 0; i < 23; i++) {
				setRow(i, getRow(i+1));
			}
		}
	}
}