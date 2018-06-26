// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef PIN_IN_INVERT_H
#define PIN_IN_INVERT_H

#include "hwlib.hpp"

class pin_in_invert : public hwlib::pin_in {
private:
	hwlib::pin_in & pin;
public:
	pin_in_invert(hwlib::pin_in & p): pin(p) {}
	
	bool get(hwlib::buffering buf = hwlib::buffering::unbuffered) override {
		return !pin.get(buf);
	}
	
	void refresh() override {
		pin.refresh();
	}
	
}; // class pin_in_invert

#endif // PIN_IN_INVERT_H