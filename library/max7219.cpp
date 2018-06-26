// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "max7219.hpp"

void max7219::sendData(
	uint_fast8_t address,
	uint_fast8_t d
) {
	uint8_t buff[size*2];
	for(unsigned int i = 0; i < size; i++) {
		buff[i*2] = address;
		buff[i*2+1] = d;
	}
	bus.write_and_read( sel, size*2, buff, nullptr );
}

void max7219::clear() {
	for(uint_fast8_t adr = 0x01; adr <= 0x08; adr++) {
		sendData(adr, 0x00);
	}
	for(unsigned int i = 0; i<6; i++) {
		screens[i] = screen();
	}
}

void max7219::init() {
	sendData(0x0F, 0x00); // test-mode(off)
	sendData(0x0C, 0x01); // shutdown-mode(off)
	sendData(0x0A, 0x0F); // brightness(full)
	sendData(0x0B, 0x07); // scan(all)
	sendData(0x09, 0x00); // Decode-Mode(off)
	
	clear();
}

bool max7219::getPixel(unsigned int x, unsigned int y) {
	if(x >= size_x*8) x = (size_x*8)-1;
	if(y >= size_y*8) y = (size_y*8)-1;
	unsigned int x_screen = x >> 3;
	unsigned int y_screen = y >> 3;
	
	screen s = screens[size_x*y_screen+x_screen];
	
	return s.getPixel(x&0x07, y&0x07);
}

void max7219::setPixel(unsigned int x, unsigned int y, const bool b) {
	if(x >= size_x*8) x = (size_x*8)-1;
	if(y >= size_y*8) y = (size_y*8)-1;
	unsigned int x_screen = x >> 3;
	unsigned int y_screen = y >> 3;
	
	unsigned int s = size_x*y_screen+x_screen;
	uint8_t d = screens[s].setPixel(x&0x07, y&0x07, b);
	
	uint8_t out[size*2];
	
	for(unsigned int i = 0; i < size; i++) {
		if(i == s) {
			out[i*2]  = (y&0x07)+1;
			out[i*2+1]= d;
		} else {
			out[i*2]  = 0;
			out[i*2+1]= 0;
		}
	}
	
	bus.write_and_read( sel, size*2, out, nullptr );
}

void max7219::setRow(unsigned int y, const uint8_t data[]) {
	if(y >= size_y*8) y = (size_y*8)-1;
	unsigned int y_screen = y >> 3;
	
	unsigned int offset = size_x*y_screen;
	
	uint8_t out[size*2];
	
	for(unsigned int i = 0; i < size; i++) {
		out[i*2]  = 0;
		out[i*2+1]= 0;
	}
	
	for(unsigned int x = 0; x < size_x; x++) {
			uint8_t d = data[x];
			screens[x+offset].setRow(y&0x07, d);
			out[(x+offset)*2]  = (y&0x07)+1;
			out[(x+offset)*2+1]= d;
	}
	
	bus.write_and_read( sel, size*2, out, nullptr );
}

uint8_t * max7219::getRow(unsigned int y) {
	unsigned int offset = (y >> 3) * size_x;
	uint8_t out[size_x];
	for(unsigned int x = 0; x < size_x; x++) {
		out[x] = screens[x+offset].getRow(y&0x07);
	}
	
	uint8_t * point = &out[0];
	return point;
}