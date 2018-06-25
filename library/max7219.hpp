#ifndef MAX7219_H
#define MAX7219_H

#include "screen.hpp"
#include "hwlib.hpp"

class max7219 {
private:
	hwlib::spi_bus & bus;
	hwlib::pin_out & sel;
	
	const unsigned int size_x;
	const unsigned int size_y;
	const unsigned int size;
	screen screens[];
	
public:
	void sendData(uint_fast8_t adress, uint_fast8_t d);
	
	void clear();

	void init();
	
	max7219(hwlib::spi_bus & bus, hwlib::pin_out & sel, const unsigned int x, const unsigned int y): bus(bus), sel(sel),size_x(x),size_y(y),size(x*y) {
		init();
		for(unsigned int i = 0; i<size; i++) {
			screens[i] = screen();
		}
	}
	
	void setPixel(unsigned int x, unsigned int y, bool b);
	
	void setRow(unsigned int y, uint8_t data[]);
	
	uint8_t * getRow(unsigned int y);
		
}; // class max7219

#endif // MAX7219_H