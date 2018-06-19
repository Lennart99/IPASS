#ifndef MAX7219_H
#define MAX7219_H

#include "screen.hpp"
#include "hwlib.hpp"

class max7219 {
private:
	hwlib::spi_bus & bus;
	hwlib::pin_out & sel;
	
	unsigned int size_x;
	unsigned int size_y;
	unsigned int size = size_x*size_y;
	screen screens[];
	
public:
	void sendData(
		uint_fast8_t adress,
		uint_fast8_t d
	) {
		uint8_t buff[size*2];
		for(unsigned int i = 0; i < size; i++) {
			buff[i*2] = adress;
			buff[i*2+1] = d;
		}
		bus.write_and_read( sel, size*2, buff, nullptr );
	}
	
	void clear() {
		for(uint_fast8_t adr = 0x01; adr <= 0x08; adr++) {
			sendData(adr, 0x00);
		}
	}

	void init() {
		sendData(0x0F, 0x00); // test-mode(off)
		sendData(0x0C, 0x01); // shutdown-mode(off)
		sendData(0x0A, 0x0F); // brightness
		sendData(0x0B, 0x07); // scan(all)
		sendData(0x09, 0x00); // Decode-Mode(off)
		
		clear();
	}
	
	max7219(hwlib::spi_bus & bus, hwlib::pin_out & sel, unsigned int x, unsigned int y): bus(bus), sel(sel),size_x(x),size_y(y) {
		init();
		for(unsigned int i = 0; i<x*y; i++) {
			screens[i] = screen();
		}
	}
	
	void setPixel(unsigned int x, unsigned int y, bool b) {
		if(x >= size_x*8) x = (size_x*8)-1;
		if(y >= size_y*8) y = (size_y*8)-1;
		unsigned int x_screen = x >> 3;
		unsigned int y_screen = y >> 3;
		
		unsigned int s = size_x*y_screen+x_screen;
		uint8_t d = screens[s].setPixel(x&0x07, y&0x07, b);
		
		uint8_t out[size*2];
		
		for(unsigned int i = 0; i < size; i++) {
			if(i == s) {
				out[i*2]  = (y&0x07)+1;
				out[i*2+1]= d;
			} else {
				out[i*2]  = 0;
				out[i*2+1]= 0;
			}
		}
		
		bus.write_and_read( sel, size*2, out, nullptr );
	}
		
}; // class max7219

#endif // MAX7219_H