// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "../library/screen.hpp"

TEST_CASE( "sizeof" ) {
	matrix::screen s;
	REQUIRE( sizeof(s) == 8 );
	for(unsigned int y = 0; y < 8; y++) {
		s.setRow(y, 0xFF);
   }
   REQUIRE( sizeof(s) == 8 );
}

TEST_CASE( "setPixel, array of 3" ) {
   matrix::screen screens[3];
   
   screens[0] = matrix::screen();
   screens[1] = matrix::screen();
   screens[2] = matrix::screen();
   
   uint8_t d = screens[1].setPixel(3,3,true);
   REQUIRE( d == 0b00010000 );
}

TEST_CASE( "setPixel, x=0" ) {
   matrix::screen s;
   uint8_t d = s.setPixel(0,3,true);
   REQUIRE( d == 0b10000000 );
   uint8_t d2 = s.setPixel(0,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=1" ) {
   matrix::screen s;
   uint8_t d = s.setPixel(1,3,true);
   REQUIRE( d == 0b01000000 );
   uint8_t d2 = s.setPixel(1,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=2" ) {
   matrix::screen s;
   uint8_t d = s.setPixel(2,3,true);
   REQUIRE( d == 0b00100000 );
   uint8_t d2 = s.setPixel(2,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=3" ) {
   matrix::screen s;
   uint8_t d = s.setPixel(3,3,true);
   REQUIRE( d == 0b00010000 );
   uint8_t d2 = s.setPixel(3,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=4" ) {
   matrix::screen s;
   uint8_t d = s.setPixel(4,3,true);
   REQUIRE( d == 0b00001000 );
   uint8_t d2 = s.setPixel(4,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=5" ) {
   matrix::screen s;
   uint8_t d = s.setPixel(5,3,true);
   REQUIRE( d == 0b00000100 );
   uint8_t d2 = s.setPixel(5,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=6" ) {
   matrix::screen s;
   uint8_t d = s.setPixel(6,3,true);
   REQUIRE( d == 0b00000010 );
   uint8_t d2 = s.setPixel(6,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=7" ) {
   matrix::screen s;
   uint8_t d = s.setPixel(7,3,true);
   REQUIRE( d == 0b00000001 );
   uint8_t d2 = s.setPixel(7,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=8" ){
   matrix::screen s;
   uint8_t d = s.setPixel(8,3,true);
   REQUIRE( d == 0b10000000 );
   uint8_t d2 = s.setPixel(8,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "getPixel, x=0" ) {
   matrix::screen s;
   s.setPixel(0,3,true);
   bool d = s.getPixel(0,3);
   REQUIRE( d == true );
   
   s.setPixel(0,3,false);
   bool d2 = s.getPixel(0,3);
   REQUIRE( d2 == false );
}

TEST_CASE( "getPixel, x=7" ) {
   matrix::screen s;
   s.setPixel(7,3,true);
   bool d = s.getPixel(7,3);
   REQUIRE( d == true );
   
   s.setPixel(7,3,false);
   bool d2 = s.getPixel(7,3);
   REQUIRE( d2 == false );
}

TEST_CASE( "getPixel, x=8" ){
   matrix::screen s;
   s.setPixel(8,3,true);
   bool d = s.getPixel(8,3);
   REQUIRE( d == true );
   
   s.setPixel(8,3,false);
   bool d2 = s.getPixel(8,3);
   REQUIRE( d2 == false );
}

TEST_CASE( "getRow, x=0" ) {
   matrix::screen s;
   s.setPixel(0,3,true);
   uint8_t d = s.getRow(3);
   REQUIRE( d == 0b10000000 );
   
   s.setPixel(0,3,false);
   uint8_t d2 = s.getRow(3);
   REQUIRE( d2 == 0 );
}

TEST_CASE( "getRow, x=7" ) {
   matrix::screen s;
   s.setPixel(7,3,true);
   uint8_t d = s.getRow(3);
   REQUIRE( d == 0b00000001 );
   
   s.setPixel(0,3,true);
   uint8_t d1 = s.getRow(3);
   REQUIRE( d1 == 0b10000001 );
   
   s.setPixel(7,3,false);
   uint8_t d2 = s.getRow(3);
   REQUIRE( d2 == 0b10000000 );
   
   s.setPixel(0,3,false);
   uint8_t d3 = s.getRow(3);
   REQUIRE( d3 == 0 );
}

TEST_CASE( "getRow, x=8" ){
   matrix::screen s;
   s.setPixel(8,3,true);
   uint8_t d = s.getRow(3);
   REQUIRE( d == 0b10000000 );
   
   s.setPixel(8,3,false);
   uint8_t d2 = s.getRow(3);
   REQUIRE( d2 == 0 );
}

TEST_CASE( "setRow, data=255" ){
   matrix::screen s;
   s.setRow(3,0xFF);
   uint8_t d = s.getRow(3);
   REQUIRE( d == 0xFF );
   
   s.setRow(3,0);
   uint8_t d2 = s.getRow(3);
   REQUIRE( d2 == 0 );
}

TEST_CASE( "setRow, data=1" ){
   matrix::screen s;
   s.setRow(3,0x01);
   uint8_t d = s.getRow(3);
   REQUIRE( d == 0x01 );
   
   s.setRow(3,0);
   uint8_t d2 = s.getRow(3);
   REQUIRE( d2 == 0 );
}

TEST_CASE( "setRow, data=128" ){
   matrix::screen s;
   s.setRow(3,128);
   uint8_t d = s.getRow(3);
   REQUIRE( d == 128 );
   
   s.setRow(3,0);
   uint8_t d2 = s.getRow(3);
   REQUIRE( d2 == 0 );
}