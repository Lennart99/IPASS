#ifndef PIECE_H
#define PIECE_H

#include "board.hpp"
#include "pin_in_invert.hpp"

class piece {
private:
	board window;
	
public:
	piece(max7219 & w): window(w)
		 {}

	void run();
		
}; // class piece

#endif // PIECE_H