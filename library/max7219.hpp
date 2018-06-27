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
 * \mainpage
 * \author Lennart Jensen (lennart.jensen@student.hu.nl)
 * \version 1.0
 * \copyright boost license
 *
 * -------------------------------------------------------------------------
 *
 * This library is created for the ipass project of year 2017-2018.
 * With this library multiple MAX7219 matrixes can be used as one display.
 * this library gives you the option to set independent pixels, or whole rows.
 * As well sending data to all displays at the same time and clearing the whole display
 *
 * The entire library is written in C++ OO fashion with C++ 11.
 * The library is dependent on hwlib (https://github.com/wovo/hwlib, © Wouter van Ooijen).
 *
 * GitHub: https://github.com/Lennart99/IPASS
 */

/**
 * \page use Use
 * For usage examples of the library, please see the
 * demo on the github.
 *
 * The library is a layer between the presentation layer and the
 * hardware layer. The library user is responsible for providing
 * a hardware implementation for the spi port and the cs pin.
 */

/**
 * \brief
 * matrix namespace
 * \details
 * The matrix namespace contains the whole library.
 */

namespace matrix {

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
template<std::size_t _x, std::size_t _y>
class max7219 {
private:
	hwlib::spi_bus & bus;
	hwlib::pin_out & sel; 
	
	const uint8_t size_x;
	const uint8_t size_y;
	const uint8_t size;
	screen screens[_x*_y];
public:
	/**
	 * @brief sends 2 bytes of data to all connected LED-matixes at the same time
	 * @param address the first byte, represents the address of the register to set, only the last 4 bits are used, but all 8 bits are sent
	 * @param d the second byte, represents the data to save in the register
	 */
	void sendData(const uint_fast8_t address, const uint_fast8_t d) {
		uint8_t buff[size*2];
		for(unsigned int i = 0; i < size; i++) {
			buff[i*2] = address;
			buff[i*2+1] = d;
		}
		bus.write_and_read( sel, size*2, buff, nullptr );
	}
	
	/**
	 * @brief clears all LED-matixes at the same time, by sending commands to set registers 1 till 9 to 0
	 */
	void clear() {
		for(uint_fast8_t adr = 0x01; adr <= 0x08; adr++) {
			sendData(adr, 0x00);
		}
		for(unsigned int i = 0; i<size; i++) {
			screens[i] = screen();
		}
	}
private:
	void init() {
		sendData(0x0F, 0x00); // test-mode(off)
		sendData(0x0C, 0x01); // shutdown-mode(off)
		sendData(0x0A, 0x0F); // brightness(full)
		sendData(0x0B, 0x07); // scan(all)
		sendData(0x09, 0x00); // Decode-Mode(off)
		
		clear();
	}
	
public:
	max7219(hwlib::spi_bus & bus, hwlib::pin_out & sel): bus(bus), sel(sel),size_x(_x),size_y(_y),size(_x*_y)
	{
		init();
	}	
	
	/**
	 * @brief sets the state of an pixel
	 * @param x the X coordinate of the pixel to set
	 * @param y the Y coordinate of the pixel to set
	 * @param b the state to set the pixel to (on=true, off=false)
	 */
	void setPixel(unsigned int x, unsigned int y, const bool b) {
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
	
	/**
	 * @brief gets the state of an pixel as an boolean
	 * @param x the X coordinate of the pixel to get the state of
	 * @param y the Y coordinate of the pixel to get the state of
	 * @return the state of the pixel (on=true, off=false)
	 */
	bool getPixel(unsigned int x, unsigned int y) {
		if(x >= size_x*8) x = (size_x*8)-1;
		if(y >= size_y*8) y = (size_y*8)-1;
		unsigned int x_screen = x >> 3;
		unsigned int y_screen = y >> 3;
		
		screen s = screens[size_x*y_screen+x_screen];
		
		return s.getPixel(x&0x07, y&0x07);
	}
	
	/**
	 * @brief sets an whole row at once
	 * @details an array is used because it is not pre-defined how much LED-matixes will be stacked next to each other
	 * @param y the Y coordinate of the row to set
	 * @param data the bytes to set the row to
	 */
	void setRow(unsigned int y, const uint8_t data[]) {
		if(y >= size_y*8) y = (size_y*8)-1;
		unsigned int y_screen = y >> 3;
		
		unsigned int offset = size_x*y_screen;
		
		uint8_t out[size*2];
		
		for(unsigned int i = 0; i < size*2; i++) {
			out[i]  = 0x00;
		}
		
		for(unsigned int x = 0; x < size_x; x++) {
				uint8_t d = data[x];
				screens[x+offset].setRow(y&0x07, d);
				out[(x+offset)*2]  = (y&0x07)+1;
				out[(x+offset)*2+1]= d;
		}
		
		bus.write_and_read( sel, size*2, out, nullptr );
	}
	
	/**
	 * @brief gets an whole row at once
	 * @details an array is used because it is not pre-defined how much LED-matixes will be stacked next to each other
	 * 			and because we can't return an array, we return the pointer to the first byte
	 * @param y the Y coordinate of the row to get the bytes from
	 * @return an pointer to the first byte out of the array of bytes that represents the row
	 */
	uint8_t * getRow(unsigned int y) {
		unsigned int offset = (y >> 3) * size_x;
		uint8_t out[size_x];
		for(unsigned int x = 0; x < size_x; x++) {
			out[x] = screens[x+offset].getRow(y&0x07);
		}
		
		uint8_t * point = &out[0];
		return point;
	}
		
}; // class max7219

}; //namespace matrix

#endif // MAX7219_H