// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

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
	
	void print();
	void remove();
	
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