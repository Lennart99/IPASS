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
	
	void removeFullRows();
		
}; // class board

#endif // BOARD_H