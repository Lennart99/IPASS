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
		for(unsigned int y = 0; y < 8*2; y++) {
			for(unsigned int x = 0; x < 8*2; x++) {
				screen.setPixel(x,y,true);
				hwlib::wait_ms(500);
				screen.setPixel(x,y,false);
			}
		}
	}
}