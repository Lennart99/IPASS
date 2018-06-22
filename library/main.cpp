#include "max7219.hpp"

int main() {
	// kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
	auto din = hwlib::target::pin_out(hwlib::target::pins::d12);
	auto cs  = hwlib::target::pin_out(hwlib::target::pins::d11);
	auto clk = hwlib::target::pin_out(hwlib::target::pins::d10);
	
	auto spi = hwlib::spi_bus_bit_banged_sclk_mosi_miso(clk, din, hwlib::pin_in_dummy);
	auto screen = max7219(spi, cs, 2, 2);
	for(;;) {
		/*for(int y = 8; y < 8*2; y++) {
			for(int x = 0; x < 8*2; x++) {
				screen.setPixel(x,y,true);
				hwlib::wait_ms(500);
				screen.setPixel(x,y,false);
			}
		}*/ 
		screen.setPixel(8,11,true);
		hwlib::wait_ms(500);
		screen.setPixel(8,11,false);
		
		screen.setPixel(9,11,true);
		hwlib::wait_ms(500);
		screen.setPixel(9,11,false);
		
		screen.setPixel(10,11,true);
		hwlib::wait_ms(500);
		screen.setPixel(10,11,false);
		
		screen.setPixel(11,11,true);
		hwlib::wait_ms(500);
		screen.setPixel(11,11,false);
		
		screen.setPixel(12,11,true);
		hwlib::wait_ms(500);
		screen.setPixel(12,11,false);
		
		screen.setPixel(13,11,true);
		hwlib::wait_ms(500);
		screen.setPixel(13,11,false);
		
		screen.setPixel(14,11,true);
		hwlib::wait_ms(500);
		screen.setPixel(14,11,false);
		
		screen.setPixel(15,11,true);
		hwlib::wait_ms(500);
		screen.setPixel(15,11,false);
		
		
		
		screen.setPixel(8,12,true);
		hwlib::wait_ms(500);
		screen.setPixel(8,12,false);
		
		screen.setPixel(9,12,true);
		hwlib::wait_ms(500);
		screen.setPixel(9,12,false);
		
		screen.setPixel(10,12,true);
		hwlib::wait_ms(500);
		screen.setPixel(10,12,false);
		
		screen.setPixel(11,12,true);
		hwlib::wait_ms(500);
		screen.setPixel(11,12,false);
		
		screen.setPixel(12,12,true);
		hwlib::wait_ms(500);
		screen.setPixel(12,12,false);
		
		screen.setPixel(13,12,true);
		hwlib::wait_ms(500);
		screen.setPixel(13,12,false);
		
		screen.setPixel(14,12,true);
		hwlib::wait_ms(500);
		screen.setPixel(14,12,false);
		
		screen.setPixel(15,12,true);
		hwlib::wait_ms(500);
		screen.setPixel(15,12,false);
	}
}