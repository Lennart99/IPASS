#ifndef BOARD_H
#define BOARD_H

#include "max7219.hpp"

class board {
private:
	max7219 & window;
	
public:
	board(max7219 & w): window(w)
		 {}

	uint16_t getRow(unsigned int y);
	
	void setRow(unsigned int y, uint16_t d);
	
	bool getPixel(unsigned int y, unsigned int x);
	
	void setPixel(unsigned int y, unsigned int x, bool b);
	
	void removeFullRows();
		
}; // class board

#endif // BOARD_H