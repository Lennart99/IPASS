//#include "screen.hpp"
#include <iostream>
#include <stdint.h>
using namespace std;

int main() {
	/*
	screen screens[4];
	screens[3] = screen();
	
	unsigned int x = 8;
	unsigned int y= 12;
	
	unsigned int d = screens[3].setPixel(x&0x07, y&0x07, true);
	cout << d << endl;
	
	unsigned int d2 = screens[3].setPixel(x&0x07, y&0x07, false);
	cout << d2 << endl;
	*/
	
	uint8_t out[2];
	out[0] = 'A';
	out[1] = 'b';
	
	uint8_t * point = out;
	
	uint8_t in[2] = { *point, *(point+1) };
	
	cout << "in[0]=" << in[0] << ", in[1]=" << in[1] << endl;
}