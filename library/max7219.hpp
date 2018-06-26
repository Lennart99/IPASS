// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef MAX7219_H
#define MAX7219_H

#include "screen.hpp"
#include "hwlib.hpp"

/**
 * @class max7219
 * @brief
 * class to control multiple max7219 LED-matixes as one display
 * @details
 * The pixels are saved in separate screen instances for every max7219
 * \n
 * for an configuration of 2x3 matrixes it should be wired as folows:
 * \n
 * configuration:\n
 * 	1	2\n
 * 	3	4\n
 * 	5	6\n
 * \n
 * due > 6 > 5 > 4 > 3 > 2 > 1
 */
class max7219 {
private:
	hwlib::spi_bus & bus;
	hwlib::pin_out & sel;
	
	const uint8_t size_x;
	const uint8_t size_y;
	const uint8_t size;
	screen screens[6];
	
	void init();
	
public:
	max7219(hwlib::spi_bus & bus, hwlib::pin_out & sel, uint8_t x, uint8_t y): bus(bus), sel(sel),size_x(x),size_y(y),size(x*y)
	{
		init();
	}
	
	/**
	 * @brief sends 2 bytes of data to all connected LED-matixes at the same time
	 * @param address the first byte, represents the address of the register to set, only the last 4 bits are used, but all 8 bits are sent
	 * @param d the second byte, represents the data to save in the register
	 */
	void sendData(uint_fast8_t address, uint_fast8_t d);
	
	/**
	 * @brief clears all LED-matixes at the same time, by sending commands to set registers 1 till 9 to 0
	 */
	void clear();
	
	/**
	 * @brief sets the state of an pixel
	 * @param x the X coordinate of the pixel to set
	 * @param y the Y coordinate of the pixel to set
	 * @param b the state to set the pixel to (on=true, off=false)
	 */
	void setPixel(unsigned int x, unsigned int y, const bool b);
	
	/**
	 * @brief gets the state of an pixel as an boolean
	 * @param x the X coordinate of the pixel to get the state of
	 * @param y the Y coordinate of the pixel to get the state of
	 * @return the state of the pixel (on=true, off=false)
	 */
	bool getPixel(unsigned int x, unsigned int y);
	
	/**
	 * @brief sets an whole row at once
	 * @details an array is used because it is not pre-defined how much LED-matixes will be stacked next to each other
	 * @param y the Y coordinate of the row to set
	 * @param data the bytes to set the row to
	 */
	void setRow(unsigned int y, const uint8_t data[]);
	
	/**
	 * @brief gets an whole row at once
	 * @details an array is used because it is not pre-defined how much LED-matixes will be stacked next to each other
	 * 			and because we can't return an array, we return the pointer to the first byte
	 * @param y the Y coordinate of the row to get the bytes from
	 * @return an pointer to the first byte out of the array of bytes that represents the row
	 */
	uint8_t * getRow(unsigned int y);
		
}; // class max7219

#endif // MAX7219_H