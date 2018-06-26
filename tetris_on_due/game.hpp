// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef GAME_H
#define GAME_H

#include "board.hpp"
#include "piece.hpp"
#include "pin_in_invert.hpp"

class game {
private:
	board window;
	piece p;
	pin_in_invert sw_left;
	pin_in_invert sw_right;
	pin_in_invert sw_down;
	
	bool tryToMoveDown();
	
public:
	game(max7219 & w, hwlib::pin_in & l, hwlib::pin_in & r, hwlib::pin_in & d): window(w),p(window),sw_left(l),sw_right(r),sw_down(d)
		 {}

	void run();
		
}; // class game

#endif // GAME_H