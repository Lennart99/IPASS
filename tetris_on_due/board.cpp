// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
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
	unsigned int max = 24;
	for(unsigned int y = 0; y < max; y++) {
		// remove all rows that are directly on top of the first one
		while(getRow(y) == 0xFFFF) {// full row
			// shift everything down by one
			for(unsigned int i = 0; i < 23; i++) {
				setRow(i, getRow(i+1)); // copy row from above
			}
			setRow(max-1, 0x000); // remove row that isn't overridden by another one
			max--; // row is empty, no need to check empty rows when we know they are empty
		}
	}
}