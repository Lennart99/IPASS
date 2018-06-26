// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

/**
 * @class screen
 * @brief class to save the pixels of one LED-matix
 * @details this class is used by the max7219 class to save the pixels of the LED-matixes 
 */
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
	
	/**
	 * @brief sets the state of an pixel
	 * @details this doesn't effect the hardware in any way, it only changes the data in the array
	 * 			the hardware is handled by the max7219 class
	 * @param x the X coordinate of the pixel in this matrix(must be lower then 8)
	 * @param y the Y coordinate of the pixel in this matrix(must be lower then 8)
	 * @param b the state to set the pixel to (on=true, off=false)
	 * @return the full row, this way we can send the correct data to the matrixes without the need to cast getRow()
	 */
	uint8_t setPixel(unsigned int x, unsigned int y, const bool b);
	
	/**
	 * @brief gets the state of an pixel
	 * @param x the X coordinate of the pixel in this matrix(must be lower then 8)
	 * @param y the Y coordinate of the pixel in this matrix(must be lower then 8)
	 * @return the state of the pixel (on=true, off=false)
	 */
	bool getPixel(unsigned int x, unsigned int y);
	
	/**
	 * @brief sets an whole row at once
	 * @details this doesn't effect the hardware in any way, it only changes the data in the array
	 * 			the hardware is handled by the max7219 class
	 * @param y the Y coordinate of the row in this matrix(must be lower then 8)
	 * @param data the byte to set the row to
	 */
	void setRow(unsigned int y, const uint8_t data);
	
	/**
	 * @brief gets an whole row at once
	 * @param y the Y coordinate of the row in this matrix(must be lower then 8)
	 * @return the byte that represents the row
	 */
	uint8_t getRow(unsigned int y);
		
}; // class screen

#endif // SCREEN_H