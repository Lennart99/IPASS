#include "max7219.hpp"

int main() {
	// kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
	auto din = hwlib::target::pin_out(hwlib::target::pins::d12);
	auto cs  = hwlib::target::pin_out(hwlib::target::pins::d11);
	auto clk = hwlib::target::pin_out(hwlib::target::pins::d10);
	
	auto spi = hwlib::spi_bus_bit_banged_sclk_mosi_miso(clk, din, hwlib::pin_in_dummy);
	auto b = max7219(spi, cs, 2,1);
	b.setPixel(7, 0, true);
	b.setPixel(8, 0, true);
	b.setPixel(7, 1, true);
	b.setPixel(8, 1, true);
	/*for(;;) {
		b.setPixel(8,11,true);
		hwlib::wait_ms(500);
		b.setPixel(8,11,false);
		
		b.setPixel(9,11,true);
		hwlib::wait_ms(500);
		b.setPixel(9,11,false);
		
		b.setPixel(10,11,true);
		hwlib::wait_ms(500);
		b.setPixel(10,11,false);
		
		b.setPixel(11,11,true);
		hwlib::wait_ms(500);
		b.setPixel(11,11,false);
		
		b.setPixel(12,11,true);
		hwlib::wait_ms(500);
		b.setPixel(12,11,false);
		
		b.setPixel(13,11,true);
		hwlib::wait_ms(500);
		b.setPixel(13,11,false);
		
		b.setPixel(14,11,true);
		hwlib::wait_ms(500);
		b.setPixel(14,11,false);
		
		b.setPixel(15,11,true);
		hwlib::wait_ms(500);
		b.setPixel(15,11,false);
		
		
		
		b.setPixel(8,12,true);
		hwlib::wait_ms(500);
		b.setPixel(8,12,false);
		
		b.setPixel(9,12,true);
		hwlib::wait_ms(500);
		b.setPixel(9,12,false);
		
		b.setPixel(10,12,true);
		hwlib::wait_ms(500);
		b.setPixel(10,12,false);
		
		b.setPixel(11,12,true);
		hwlib::wait_ms(500);
		b.setPixel(11,12,false);
		
		b.setPixel(12,12,true);
		hwlib::wait_ms(500);
		b.setPixel(12,12,false);
		
		b.setPixel(13,12,true);
		hwlib::wait_ms(500);
		b.setPixel(13,12,false);
		
		b.setPixel(14,12,true);
		hwlib::wait_ms(500);
		b.setPixel(14,12,false);
		
		b.setPixel(15,12,true);
		hwlib::wait_ms(500);
		b.setPixel(15,12,false);
	}*/
}