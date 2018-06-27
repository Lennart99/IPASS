// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef FAKE_PIN_H
#define FAKE_PIN_H

#include "hwlib.hpp"

class fake_pin_out : public hwlib::pin_out {
private:
	unsigned int n_pulses = 0;
	bool on = false;

public:
	void set(bool b, hwlib::buffering buf = hwlib::buffering::unbuffered) override {
		if(!b) {
			on = false;
		} else {
			if(!on && buf == hwlib::buffering::unbuffered) {
				on = true;
				n_pulses ++;
			}
		}
	}
	
	unsigned int getN_pulses() {
		return n_pulses;
	}
};

#endif // FAKE_PIN_H