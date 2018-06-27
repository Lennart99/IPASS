// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "game.hpp"

bool game::tryToMoveDown() {
	if(!p.moveDown()) {
		window.removeFullRows();
		if(!p.place()) {
			// game over
			return true;
		}
	}
	return false;
}

void game::run() {
	uint64_t end = 0;
	for(;;) {
		end = hwlib::now_us() + 1'000'000;// one second
		while( hwlib::now_us() < end ) {
			if(sw_left.get() && !sw_right.get()) {// do nohing when both buttons are pressed
				if(p.moveLeft()) {
					hwlib::wait_ms(150);
				}
			} else if(sw_right.get() && !sw_left.get()) {// do nohing when both buttons are pressed
				if(p.moveRight()) {
					hwlib::wait_ms(150);
				}
			}
			
			if(sw_down.get()) {
				if(tryToMoveDown()) {
					break;
				}
				hwlib::wait_ms(150);
			}
		}
		
		if(tryToMoveDown()) {
			break;
		}
	}
}