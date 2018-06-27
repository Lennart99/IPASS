// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

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

bool board::getPixel(unsigned int x, unsigned int y) {
	return window.getPixel(x,y);
}

void board::setPixel(unsigned int x, unsigned int y, bool b) {
	window.setPixel(x,y,b);
}

void board::removeFullRows() {
	for(unsigned int y = 0; y < 24; y++) {
		if(getRow(y) == 0xFFFF) {// full row
			setRow(0,0x00);
			setRow(y, 0x00);
			// shift everything down by one
			for(unsigned int i = y; i > 0; i--) {
				setRow(i, getRow(i-1)); // copy row from above
			}
		}
	}
}
