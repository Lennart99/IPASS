#include "game.hpp"

int main() {
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	auto din = hwlib::target::pin_out(hwlib::target::pins::d12);
	auto cs  = hwlib::target::pin_out(hwlib::target::pins::d11);
	auto clk = hwlib::target::pin_out(hwlib::target::pins::d10);
	
	auto spi = hwlib::spi_bus_bit_banged_sclk_mosi_miso(clk, din, hwlib::pin_in_dummy);
	
	auto w = max7219(spi, cs, 2, 3);
	auto b = board(w);
	//auto b = board(w);
	//auto left  = hwlib::target::pin_in(hwlib::target::pins::d2);
	//auto right = hwlib::target::pin_in(hwlib::target::pins::d3);
	
	//auto g = game(w,left,right);
	//g.run();
	
	//auto p = piece(b); p.place();
	b.setPixel(7, 0, true);
	b.setPixel(8, 0, true);
	b.setPixel(7, 1, true);
	b.setPixel(8, 1, true);
}