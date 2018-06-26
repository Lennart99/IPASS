// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

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
	
	bool getPixel(unsigned int x, unsigned int y);
	
	void setRow(unsigned int y, uint8_t data);
	
	uint8_t getRow(unsigned int y);
		
}; // class screen

#endif // SCREEN_H