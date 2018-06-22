#include "screen.hpp"

// needed to get Catch working with MinGW
#define TWOBLUECUBES_CATCH_REPORTER_JUNIT_HPP_INCLUDED
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE( "setPixel, array, 3" ){
   screen screens[3];
   
   screens[0] = screen();
   screens[1] = screen();
   screens[2] = screen();
   
   uint8_t d = screens[1].setPixel(3,3,true);
   REQUIRE( d == 0b00010000 );
}

TEST_CASE( "setPixel, x=0" ){
   screen s;
   uint8_t d = s.setPixel(0,3,true);
   REQUIRE( d == 0b10000000 );
}

TEST_CASE( "setPixel, x=0, off" ){
   screen s;
   uint8_t d = s.setPixel(0,3,true);
   uint8_t d2 = s.setPixel(0,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=1, y=4" ){
   screen s;
   uint8_t d = s.setPixel(1,4,true);
   REQUIRE( d == 0b01000000 );
   uint8_t d2 = s.setPixel(1,4,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=1" ){
   screen s;
   uint8_t d = s.setPixel(1,3,true);
   REQUIRE( d == 0b01000000 );
}

TEST_CASE( "setPixel, x=1, off" ){
   screen s;
   uint8_t d = s.setPixel(1,3,true);
   uint8_t d2 = s.setPixel(1,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=2" ){
   screen s;
   uint8_t d = s.setPixel(2,3,true);
   REQUIRE( d == 0b00100000 );
}

TEST_CASE( "setPixel, x=2, off" ){
   screen s;
   uint8_t d = s.setPixel(2,3,true);
   uint8_t d2 = s.setPixel(2,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=3" ){
   screen s;
   uint8_t d = s.setPixel(3,3,true);
   REQUIRE( d == 0b00010000 );
}

TEST_CASE( "setPixel, x=3, off" ){
   screen s;
   uint8_t d = s.setPixel(3,3,true);
   uint8_t d2 = s.setPixel(3,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=4" ){
   screen s;
   uint8_t d = s.setPixel(4,3,true);
   REQUIRE( d == 0b00001000 );
}

TEST_CASE( "setPixel, x=4, off" ){
   screen s;
   uint8_t d = s.setPixel(4,3,true);
   uint8_t d2 = s.setPixel(4,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=5" ){
   screen s;
   uint8_t d = s.setPixel(5,3,true);
   REQUIRE( d == 0b00000100 );
}

TEST_CASE( "setPixel, x=5, off" ){
   screen s;
   uint8_t d = s.setPixel(5,3,true);
   uint8_t d2 = s.setPixel(5,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=6" ){
   screen s;
   uint8_t d = s.setPixel(6,3,true);
   REQUIRE( d == 0b00000010 );
}

TEST_CASE( "setPixel, x=6, off" ){
   screen s;
   uint8_t d = s.setPixel(6,3,true);
   uint8_t d2 = s.setPixel(6,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=7" ){
   screen s;
   uint8_t d = s.setPixel(7,3,true);
   REQUIRE( d == 0b00000001 );
}

TEST_CASE( "setPixel, x=7, off" ){
   screen s;
   uint8_t d = s.setPixel(7,3,true);
   uint8_t d2 = s.setPixel(7,3,false);
   REQUIRE( d2 == 0b00000000 );
}

TEST_CASE( "setPixel, x=8" ){
   screen s;
   uint8_t d = s.setPixel(8,3,true);
   REQUIRE( d == 0b10000000 );
}

TEST_CASE( "setPixel, x=8, off" ){
   screen s;
   uint8_t d = s.setPixel(8,3,true);
   uint8_t d2 = s.setPixel(8,3,false);
   REQUIRE( d2 == 0b00000000 );
}