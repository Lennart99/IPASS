#ifndef MAX7219_H
#define MAX7219_H

#include <stdint.h>
#include "hwlib.hpp"

class max7219 {
private:
	hwlib::spi_bus & bus;
	hwlib::pin_out & sel;

	uint8_t data[8] = {
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	};
	uint8_t write_buffer[2] = {0, 0};
	
public:
	max7219(hwlib::spi_bus & bus, hwlib::pin_out & sel, unsigned int size = 2):
		bus(bus), sel(sel) {
			init();
		}
		
	void sendData(
		uint_fast8_t adress = 0x00,
		uint_fast8_t d = 0x00,
		hwlib::buffering buf = hwlib::buffering::unbuffered 
	) {
		write_buffer[0] = adress;
		write_buffer[1] = d;
		if( buf == hwlib::buffering::unbuffered ){
			bus.write_and_read( sel, 2, write_buffer, nullptr );
			write_buffer[0] = 0;
			write_buffer[1] = 0;
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
		if(x > 0x07) x = 0x07;
		if(y > 0x07) y = 0x07;
		
		uint8_t d = data[y];
		if(b) {
			d = d | (0x80 >> x);
		} else {
			d = d & ~(0x80 >> x);
		}
		data[y] = d;

		sendData(y+1, d);
	}
		
}; // class max7219

#endif // MAX7219_H