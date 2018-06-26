#include "game.hpp"

/*void sendData(
	uint_fast8_t adress,
	uint_fast8_t d,
	hwlib::spi_bus & bus,
	hwlib::pin_out & sel
) {
	hwlib::target::pin_out led = hwlib::target::pin_out(hwlib::target::pins::d13);
	uint8_t buff[8];
	for(unsigned int i = 0; i < 4; i++) {
		buff[i*2] = adress;
		buff[i*2+1] = d;
	}
	bus.write_and_read( sel, 8, buff, nullptr );
	ed.set(false);
}*/

int main() {
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	auto din = hwlib::target::pin_out(hwlib::target::pins::d12);
	auto cs  = hwlib::target::pin_out(hwlib::target::pins::d11);
	auto clk = hwlib::target::pin_out(hwlib::target::pins::d10);
	
	auto spi = hwlib::spi_bus_bit_banged_sclk_mosi_miso(clk, din, hwlib::pin_in_dummy);
	
	auto w = max7219(spi, cs, 2, 3);
	//auto b = board(w);
	
	auto left  = hwlib::target::pin_in(hwlib::target::pins::d2);
	auto right = hwlib::target::pin_in(hwlib::target::pins::d3);
	
	auto g = game(w,left,right);
	g.run();
}