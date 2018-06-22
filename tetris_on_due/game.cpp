#include "game.hpp"

void game::run() {
	for(;;) {
		uint64_t end = hwlib::now_us() + 1'0000'000;
		while( hwlib::now_us() < end ) {
			if(sw_left.get() && !sw_right.get()) {// do nohing when both buttons are pressed
				// TODO move block <<
				hwlib::wait_ms(50);
			} else if(sw_right.get() && !sw_left.get()) {// do nohing when both buttons are pressed
				// TODO move block >>
				hwlib::wait_ms(50);
			}
			
		}
		// TODO move block down
		
		// als block niet verder naar beneden kan:
			window.removeFullRows();
	}
}