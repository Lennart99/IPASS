// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef BOARD_H
#define BOARD_H

#include "../library/max7219.hpp"

class board {
private:
	max7219 & window;
	
	uint16_t getRow(unsigned int y);
	
	void setRow(unsigned int y, uint16_t d);
	
public:
	board(max7219 & w): window(w)
		 {}
	
	bool getPixel(unsigned int x, unsigned int y);
	
	void setPixel(unsigned int x, unsigned int y, bool b);
	
	/**
	 * @brief removes rows when they are fully build
	 */
	void removeFullRows();
		
}; // class board

#endif // BOARD_H