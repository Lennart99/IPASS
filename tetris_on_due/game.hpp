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
	
public:
	game(max7219 & w, hwlib::pin_in & l, hwlib::pin_in & r): window(w),p(window),sw_left(l),sw_right(r)
		 {}

	void run();
		
}; // class game

#endif // GAME_H