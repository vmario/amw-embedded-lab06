/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 *
 * Implementacja sterownika magistrali 1-Wire.
 */

#include "1wire.hpp"

#include "1wirePinout.hpp"

#include <util/delay.h>

/**
 * Timingi magistrali 1-Wire.
 * 
 * Na podstawie:
 * https://www.analog.com/en/technical-articles/1wire-communication-through-software.html
 */
enum WIRE_1_DELAY {
	WIRE_1_DELAY_A = 6, ///< Opóźnienie A.
	WIRE_1_DELAY_B = 64, ///< Opóźnienie B.
	WIRE_1_DELAY_C = 60, ///< Opóźnienie C.
	WIRE_1_DELAY_D = 10, ///< Opóźnienie D.
	WIRE_1_DELAY_E = 9, ///< Opóźnienie E.
	WIRE_1_DELAY_F = 55, ///< Opóźnienie F.
	WIRE_1_DELAY_G = 0, ///< Opóźnienie G.
	WIRE_1_DELAY_H = 480, ///< Opóźnienie H.
	WIRE_1_DELAY_I = 70, ///< Opóźnienie I.
	WIRE_1_DELAY_J = 410, ///< Opóźnienie J.
};

/**
 * Steruje linią danych.
 */
struct Wire1Data {
	/**
	 * Zwiera linię do masy.
	 */
	void ground() const
	{
		WIRE_1_DIR |= WIRE_1_DATA;
	}

	/**
	 * Zwalnia linię.
	 */
	void release() const
	{
		WIRE_1_DIR &= ~WIRE_1_DATA;
	}

	/**
	 * Odczytuje stan linii.
	 * 
	 * @return Stan na linii.
	 */
	bool read() const
	{
		return WIRE_1_PIN & WIRE_1_DATA;
	}
};

void Wire1::writeBit(bool bit) const
{
	const Wire1Data data{};
	data.ground();
	if (bit) {
		_delay_us(WIRE_1_DELAY_A);
		data.release();
		_delay_us(WIRE_1_DELAY_B);
	} else {
		_delay_us(WIRE_1_DELAY_C);
		data.release();
		_delay_us(WIRE_1_DELAY_D);
	}
}

void Wire1::writeByte(uint8_t byte) const
{
	for (uint8_t i{0}; i < 8; ++i) {
		writeBit(byte & 0x01);
		byte >>= 1;
	}
}

bool Wire1::readBit() const
{
	const Wire1Data data{};
	data.ground();
	_delay_us(WIRE_1_DELAY_A);
	data.release();
	_delay_us(WIRE_1_DELAY_E);
	bool bit{data.read()};
	_delay_us(WIRE_1_DELAY_F);
	return bit;
}

uint8_t Wire1::readByte() const
{
	uint8_t byte{0};
	
	for (uint8_t i{0}; i < 8; ++i) {
		byte |= readBit() << i;
	}
	
	return byte;
}

bool Wire1::reset() const
{
	const Wire1Data data{};
	_delay_us(WIRE_1_DELAY_G);
	data.ground();
	_delay_us(WIRE_1_DELAY_H);
	data.release();
	_delay_us(WIRE_1_DELAY_I);
	bool bit{data.read()};
	_delay_us(WIRE_1_DELAY_J);
	return !bit;
}
