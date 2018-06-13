#ifndef MAX7219_H
#define MAX7219_H

#include "screen.hpp"

class max7219 {
private:
	hwlib::spi_bus & bus;
	hwlib::pin_out & sel;
	
	unsigned int size_x;
	unsigned int size_y;
	screen screens[10][10];
	
public:
	max7219(hwlib::spi_bus & bus, hwlib::pin_out & sel, unsigned int x, unsigned int y): bus(bus), sel(sel),size_x(x),size_y(y) {
		init();
		for(unsigned int ix = 0; ix<x; ix++) {
			for(unsigned int iy = 0; iy<y; iy++) {
				screens[ix][iy] = screen();
			}
		}
	}
	
	void sendData(
		uint_fast8_t adress = 0x00,
		uint_fast8_t d = 0x00,
		hwlib::buffering buf = hwlib::buffering::unbuffered 
	) {
		uint8_t buff[2];
		buff[0] = adress;
		buff[1] = d;
		if( buf == hwlib::buffering::unbuffered ){
			bus.write_and_read( sel, 2, buff, nullptr );
		}
	}
	
	void clear() {
		for(uint8_t i = 0x01; i < 0x09; i++) {
			sendData(i, 0x00);
		}
	}
	
	void init() {
		sendData(0x0F, 0x00); // test-mode(off)
		sendData(0x0C, 0x01); // shutdown-mode(off)
		sendData(0x0A, 0x0F); // brightness
		sendData(0x0B, 0x07); // scan(all)
		sendData(0x09, 0x00); // Decode-Mode(off)
	}
	
	void setPixel(unsigned int x, unsigned int y, bool b) {
		unsigned int x_screen = x >> 3;
		unsigned int y_screen = y >> 3;
		
		screen s = screens[x_screen][y_screen];
		
		uint8_t d = s.setPixel(x&0x07, y&0x07, b);
		uint8_t out[4];
		
		for(unsigned int screenX = 0; screenX < size_x; screenX++) {
			for(unsigned int screenY = 0; screenY < size_y; screenY++) {
				unsigned int i = (size_x*screenY*2)+(screenX*2);
				if(screenX == x_screen && screenY == y_screen) {
					out[i]  = (y&0x07)+1;
					out[i+1]= d;
				} else {
					out[i]  = 0;
					out[i+1]= 0;
				}
			}
		}
		bus.write_and_read( sel, 4, out, nullptr );
		
		//sendData((y&0x07)+1, d);
	}
		
}; // class max7219

#endif // MAX7219_H