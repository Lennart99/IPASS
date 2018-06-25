#include "game.hpp"

void game::run() {
	p.place();
	for(;;) {
		/*uint64_t end = hwlib::now_us() + 500'000;// half a second
		while( hwlib::now_us() < end ) {
			if(sw_left.get() && !sw_right.get()) {// do nohing when both buttons are pressed
				p.moveLeft();
				hwlib::wait_ms(5);
			} else if(sw_right.get() && !sw_left.get()) {// do nohing when both buttons are pressed
				p.moveRight();
				hwlib::wait_ms(5);
			}
			
		}*/
		hwlib::wait_ms(500);
		p.moveDown();
		/*if(!p.canMoveDown()) {
			window.removeFullRows();// TODO points
			if(p.canBePlaced()) {
				p.place();
				// TODO points
			} else {
				// TODO game over
				break;
			}
		} else {
			p.moveDown();
		}*/
	}
}