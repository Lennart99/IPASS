#include "board.hpp"

int main() {
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	auto din = hwlib::target::pin_out(hwlib::target::pins::d12);
	auto cs  = hwlib::target::pin_out(hwlib::target::pins::d11);
	auto clk = hwlib::target::pin_out(hwlib::target::pins::d10);
	
	auto spi = hwlib::spi_bus_bit_banged_sclk_mosi_miso(clk, din, hwlib::pin_in_dummy);
	auto screen = max7219(spi, cs, 2, 3);
	
	auto left  = hwlib::target::pin_in(hwlib::target::pins::d27);
	auto right = hwlib::target::pin_in(hwlib::target::pins::d23);
	
	
}