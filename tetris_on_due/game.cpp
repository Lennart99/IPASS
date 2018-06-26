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
	if(!p.canMoveDown()) {
		window.removeFullRows();// TODO points
		if(p.canBePlaced()) {
			p.place();
			// TODO points
		} else {
			// TODO game over
			
			auto led = hwlib::target::pin_out(hwlib::target::pins::d13);
			led.set(false);
			return true;
		}
	} else {
		p.moveDown();
	}
	return false;
}

void game::run() {
	uint64_t end = 0;
	for(;;) {
		end = hwlib::now_us() + 1'000'000;// one second
		while( hwlib::now_us() < end ) {
			if(sw_left.get() && !sw_right.get()) {// do nohing when both buttons are pressed
				p.moveLeft();
				hwlib::wait_ms(150);// TODO only on success
			} else if(sw_right.get() && !sw_left.get()) {// do nohing when both buttons are pressed
				p.moveRight();
				hwlib::wait_ms(150);// TODO only on success
			}
			
			if(sw_down.get()) {
				if(tryToMoveDown()) break;
				hwlib::wait_ms(150);
			}
		}
		
		if(tryToMoveDown()) break;
	}
}