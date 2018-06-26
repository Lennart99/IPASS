#ifndef MAX7219_H
#define MAX7219_H

#include "screen.hpp"
#include "hwlib.hpp"

//template <size_t _size>
class max7219 {
private:
	hwlib::spi_bus & bus;
	hwlib::pin_out & sel;
	
	uint8_t size_x;
	uint8_t size_y;
	uint8_t size;
	screen screens[6];
	
	void init();
	
public:
	max7219(hwlib::spi_bus & bus, hwlib::pin_out & sel, uint8_t x, uint8_t y): bus(bus), sel(sel),size_x(x),size_y(y),size(x*y)
	{
		init();
		for(unsigned int i = 0; i<6; i++) {
			screens[i] = screen();
		}
	}
	
	void sendData(uint_fast8_t adress, uint_fast8_t d);
	
	void clear();
	
	void setPixel(unsigned int x, unsigned int y, bool b);
	
	bool getPixel(unsigned int x, unsigned int y);
	
	void setRow(unsigned int y, uint8_t data[]);
	
	uint8_t * getRow(unsigned int y);
		
}; // class max7219

#endif // MAX7219_H