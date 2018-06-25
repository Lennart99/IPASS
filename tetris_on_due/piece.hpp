#ifndef PIECE_H
#define PIECE_H

#include "board.hpp"
#include "pin_in_invert.hpp"

class piece {
private:
	board & window;
	uint8_t x;
	uint8_t y;
	
	bool canMoveLeft();
	bool canMoveRight();
	
	
public:
	bool canBePlaced();
	void place();
	
	piece(board & w): window(w),x(0),y(0)
		 {place();}
	
	bool canMoveDown();
	
	void moveLeft();
	void moveRight();
	void moveDown();
		
}; // class piece

#endif // PIECE_H