// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "screen.hpp"

uint8_t screen::setPixel(unsigned int x, unsigned int y, const bool b) {
	if(x > 0x07) x = x&0x07;
	if(y > 0x07) y = y&0x07;
	
	uint8_t d = data[y];
	if(b) {
		d = d | (0x80 >> x);
	} else {
		d = d & ~(0x80 >> x);
	}
	data[y] = d;

	return d;
}

bool screen::getPixel(unsigned int x, unsigned int y) {
	if(x > 0x07) x = x&0x07;
	if(y > 0x07) y = y&0x07;
	
	uint8_t d = data[y];
	
	uint16_t mask = 0x80 >> x;
	d = d & mask;
	return d != 0;
}

void screen::setRow(unsigned int y, const uint8_t d) {
	if(y > 0x07) y = y&0x07;
	data[y] = d;
}

uint8_t screen::getRow(unsigned int y) {
	if(y > 0x07) y = y&0x07;
	
	return data[y];
}