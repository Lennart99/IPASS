// ==========================================================================
// Copyright (c) Lennart Jensen (lennart.jensen@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef FAKE_spi_H
#define FAKE_spi_H

#include <stdint.h>
#include "hwlib.hpp"

class fake_spi_bus : public hwlib::spi_bus {
private:
	uint8_t data[20];
	size_t size;
public:
	void write_and_read(
		hwlib::pin_out & sel,
		const size_t n,
		const uint8_t data_out[],
		uint8_t data_in[]
	) override {
		sel.set(0);
		size = n;
		for(unsigned int i = 0; (i < n && i < 20); i++) {
			data[i] = data_out[i];
		}
		sel.set(1);
	}
	
	uint8_t * getSendData() {
		uint8_t * point = &data[0];
		return point;
	}
	
	size_t getSize() {
		return size;
	}
};

#endif // FAKE_spi_H