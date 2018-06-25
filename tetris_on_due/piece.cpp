#include "piece.hpp"

bool piece::canMoveLeft() {
	if(x == 0) {
		return false;
	} else {
		return ( !window.getPixel(x-1,y) && !window.getPixel(x-1,y+1) );
	}
}

bool piece::canMoveRight() {
	if(x <= 14) {
		return false;
	} else {
		return ( !window.getPixel(x+2,y) && !window.getPixel(x+2,y+1) );
	}
}

bool piece::canMoveDown() {
	if(y <= 22) {
		return false;
	} else {
		return ( !window.getPixel(x,y+2) && !window.getPixel(x+1,y+2) );
	}
}

void piece::moveLeft() {
	if(canMoveLeft()) {
		window.setPixel(x+1, y,   false);
		window.setPixel(x+1, y+1, false);
		window.setPixel(x-1, y,   true);
		window.setPixel(x-1, y+1, true);
		x--;
	}
}

void piece::moveRight() {
	if(canMoveRight()) {
		window.setPixel(x-1, y,   false);
		window.setPixel(x-1, y+1, false);
		window.setPixel(x+1, y,   true);
		window.setPixel(x+1, y+1, true);
		x++;
	}
}

void piece::moveDown() {
	if(canMoveDown()) {
		window.setPixel(x,   y,   false);
		window.setPixel(x+1, y,   false);
		window.setPixel(x,   y+2, true);
		window.setPixel(x+1, y+2, true);
		y++;
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
		
		window.setPixel(7, 0, true);
		window.setPixel(8, 0, true);
		window.setPixel(7, 1, true);
		window.setPixel(8, 1, true);
	//}
}