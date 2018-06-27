// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "game.hpp"

int main() {
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	auto din = hwlib::target::pin_out(hwlib::target::pins::d12);
	auto cs  = hwlib::target::pin_out(hwlib::target::pins::d11);
	auto clk = hwlib::target::pin_out(hwlib::target::pins::d10);
	
	auto spi = hwlib::spi_bus_bit_banged_sclk_mosi_miso(clk, din, hwlib::pin_in_dummy);
	
	auto w = matrix::max7219<2,3>(spi, cs);
	
	auto left  = hwlib::target::pin_in(hwlib::target::pins::d2);
	auto right = hwlib::target::pin_in(hwlib::target::pins::d3);
	auto down  = hwlib::target::pin_in(hwlib::target::pins::d4);
	
	auto g = game(w,left,right,down);
	g.run();
}