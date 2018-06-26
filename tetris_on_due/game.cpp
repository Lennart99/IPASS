#include "game.hpp"

void game::run() {
	for(;;) {
		uint64_t end = hwlib::now_us() + 1'000'000;// one second
		while( hwlib::now_us() < end ) {
			if(sw_left.get() && !sw_right.get()) {// do nohing when both buttons are pressed
				p.moveLeft();
				hwlib::wait_ms(150);
			} else if(sw_right.get() && !sw_left.get()) {// do nohing when both buttons are pressed
				p.moveRight();
				hwlib::wait_ms(150);
			}
		}
		
		if(!p.canMoveDown()) {
			window.removeFullRows();// TODO points
			if(p.canBePlaced()) {
				p.place();
				// TODO points
			} else {
				// TODO game over
				
				auto led = hwlib::target::pin_out(hwlib::target::pins::d13);
				led.set(false);
				break;
			}
		} else {
			p.moveDown();
		}
	}
}