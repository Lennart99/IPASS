// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "piece.hpp"

void piece::print() {
	window.setPixel(x,  y,   true);
	window.setPixel(x+1,y,   true);
	window.setPixel(x,  y+1, true);
	window.setPixel(x+1,y+1, true);
}

void piece::remove() {
	window.setPixel(x,  y,   false);
	window.setPixel(x+1,y,   false);
	window.setPixel(x,  y+1, false);
	window.setPixel(x+1,y+1, false);
}

bool piece::canMoveLeft() {
	if(x == 0) {
		return false;
	} else {
		return ( !window.getPixel(x-1,y) && !window.getPixel(x-1,y+1) );
	}
}

bool piece::canMoveRight() {
	if(x >= 14) {
		return false;
	} else {
		return ( !window.getPixel(x+2,y) && !window.getPixel(x+2,y+1) );
	}
}

bool piece::canMoveDown() {
	if(y >= 22) {
		return false;
	} else {
		return ( !window.getPixel(x,y+2) && !window.getPixel(x+1,y+2) );
	}
}

void piece::moveLeft() {
	if(canMoveLeft()) {
		remove();
		x--;
		print();
	}
}

void piece::moveRight() {
	if(canMoveRight()) {
		remove();
		x++;
		print();
	}
}

void piece::moveDown() {
	if(canMoveDown()) {
		remove();
		y++;
		print();
	}
}

bool piece::canBePlaced() {
	if(	window.getPixel(7, 0) ||
		window.getPixel(8, 0) ||
		window.getPixel(7, 1) ||
		window.getPixel(8, 1)
	) {
		return false;
	} else {
		return true;
	}
}

void piece::place() {
	//if(canBePlaced()) {
		x = 7;
		y = 0;
		
		print();
	//}
}