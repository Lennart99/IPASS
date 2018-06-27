// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "../library/max7219.hpp"
#include "fake_pin.hpp"
#include "fake_spi.hpp"

TEST_CASE( "fake_pin" ) {
   fake_pin_out out;
   
   out.set(true);
   REQUIRE(out.getN_pulses() == 1);
   
   out.set(false);
   REQUIRE(out.getN_pulses() == 1);
   
   out.set(true);
   REQUIRE(out.getN_pulses() == 2);
   
   out.set(true);
   REQUIRE(out.getN_pulses() == 2);
   out.set(false);
   REQUIRE(out.getN_pulses() == 2);
}

TEST_CASE( "fake_spi" ) {
   fake_spi_bus spi;
   fake_pin_out out;
   
   uint8_t data[11] = {0,1,2,3,4,5,6,7,8,9,10};
   spi.write_and_read(out, 10, data, nullptr);
   
   uint8_t * res = spi.getSendData();
   REQUIRE(spi.getSize() == 10);
   
   REQUIRE(*res == 0);
   REQUIRE(*(res+1) == 1);
   REQUIRE(*(res+2) == 2);
   REQUIRE(*(res+3) == 3);
   REQUIRE(*(res+4) == 4);
   REQUIRE(*(res+5) == 5);
   REQUIRE(*(res+6) == 6);
   REQUIRE(*(res+7) == 7);
   REQUIRE(*(res+8) == 8);
   REQUIRE(*(res+9) == 9);
   // 10 should not be sent
}

TEST_CASE( "max7219, init" ) {
	fake_spi_bus spi;
	fake_pin_out out;
	auto w = max7219<2,3>(spi, out);
	
	REQUIRE(out.getN_pulses() == (/*init*/5+/*clear*/8));
	
	REQUIRE(spi.getSize() == 12);
	uint8_t * res = spi.getSendData();
	
	REQUIRE(*res == 0x08);
	REQUIRE(*(res+1) == 0);
	REQUIRE(*(res+2) == 0x08);
	REQUIRE(*(res+3) == 0);
	REQUIRE(*(res+4) == 0x08);
	REQUIRE(*(res+5) == 0);
	REQUIRE(*(res+6) == 0x08);
	REQUIRE(*(res+7) == 0);
	REQUIRE(*(res+8) == 0x08);
	REQUIRE(*(res+9) == 0);
	REQUIRE(*(res+10) == 0x08);
	REQUIRE(*(res+11) == 0);
}

TEST_CASE( "max7219, setpixel, (0,0)" ) {
	fake_spi_bus spi;
	fake_pin_out out;
	auto w = max7219<2,2>(spi, out);
	
	w.setPixel(0,0,true);
	REQUIRE(out.getN_pulses() == (/*init*/5+/*clear*/8+/*setpixel*/1));
	
	REQUIRE(spi.getSize() == 8);
	uint8_t * res = spi.getSendData();
	
	REQUIRE(*res == 0x01);
	REQUIRE(*(res+1) == 0x80);
	REQUIRE(*(res+2) == 0);
	REQUIRE(*(res+3) == 0);
	REQUIRE(*(res+4) == 0);
	REQUIRE(*(res+5) == 0);
	REQUIRE(*(res+6) == 0);
	REQUIRE(*(res+7) == 0);
}

TEST_CASE( "max7219 of (2,2), setpixel, (8,8)" ) {
	fake_spi_bus spi;
	fake_pin_out out;
	auto w = max7219<2,2>(spi, out);
	
	w.setPixel(8,8,true);
	
	REQUIRE(spi.getSize() == 8);
	uint8_t * res = spi.getSendData();
	
	REQUIRE(*res == 0);
	REQUIRE(*(res+1) == 0);
	REQUIRE(*(res+2) == 0);
	REQUIRE(*(res+3) == 0);
	REQUIRE(*(res+4) == 0);
	REQUIRE(*(res+5) == 0);
	REQUIRE(*(res+6) == 0x01);
	REQUIRE(*(res+7) == 0x80);
}

TEST_CASE( "max7219, getpixel, (0,0)" ) {
	fake_spi_bus spi;
	fake_pin_out out;
	auto w = max7219<2,2>(spi, out);
	
	w.setPixel(0,0,true);
	REQUIRE(w.getPixel(0,0) == true);
	
	w.setPixel(0,0,true);
	REQUIRE(w.getPixel(0,0) == true);
	
	w.setPixel(0,0,false);
	REQUIRE(w.getPixel(0,0) == false);
}

TEST_CASE( "max7219 of (2,2), setRow(8,{255,255})" ) {
	fake_spi_bus spi;
	fake_pin_out out;
	auto w = max7219<2,2>(spi, out);
	
	uint8_t in[2] = {0xFF, 0xFF};
	w.setRow(8,in);
	REQUIRE(out.getN_pulses() == (/*init*/5+/*clear*/8+/*setRow*/1));
	
	REQUIRE(spi.getSize() == 8);
	uint8_t * res = spi.getSendData();
	
	REQUIRE(*res == 0);
	REQUIRE(*(res+1) == 0);
	REQUIRE(*(res+2) == 0);
	REQUIRE(*(res+3) == 0);
	REQUIRE(*(res+4) == 0x01);
	REQUIRE(*(res+5) == 0xFF);
	REQUIRE(*(res+6) == 0x01);
	REQUIRE(*(res+7) == 0xFF);
}

TEST_CASE( "max7219 of (2,2), setRow(8,{0,0})" ) {
	fake_spi_bus spi;
	fake_pin_out out;
	auto w = max7219<2,2>(spi, out);
	
	uint8_t in[2] = {0xFF, 0xFF};
	w.setRow(8,in);
	in[0] = 0;
	in[1] = 0;
	w.setRow(8,in);
	REQUIRE(out.getN_pulses() == (/*init*/5+/*clear*/8+/*setRow*/2));
	
	REQUIRE(spi.getSize() == 8);
	uint8_t * res = spi.getSendData();
	
	REQUIRE(*res == 0);
	REQUIRE(*(res+1) == 0);
	REQUIRE(*(res+2) == 0);
	REQUIRE(*(res+3) == 0);
	REQUIRE(*(res+4) == 0x01);
	REQUIRE(*(res+5) == 0);
	REQUIRE(*(res+6) == 0x01);
	REQUIRE(*(res+7) == 0);
}

TEST_CASE( "max7219 of (2,2), getRow" ) {
	fake_spi_bus spi;
	fake_pin_out out;
	auto w = max7219<2,2>(spi, out);
	
	uint8_t in[2] = {0xFF, 0xFF};
	w.setRow(8,in);
	uint8_t * d1 = w.getRow(8);
	
	uint8_t d1_0 = *d1;
	uint8_t d1_1 = *(d1+1);
	REQUIRE(d1_0 == uint8_t(255));
	REQUIRE(d1_1 == uint8_t(255));
	
	in[0] = 0;
	in[1] = 0;
	w.setRow(8,in);
	uint8_t * d2 = w.getRow(8);
	
	uint8_t d2_0 = *d2;
	uint8_t d2_1 = *(d2+1);
	REQUIRE(d2_0 == uint8_t(0));
	REQUIRE(d2_1 == uint8_t(0));
}