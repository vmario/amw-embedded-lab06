/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 *
 * Sterownik magistrali 1-Wire.
 */

#pragma once

#include <stdint.h>

/**
 * Sterownik magistrali 1-Wire.
 */
struct Wire1 {
	/**
	 * Wystawia bit na magistrali.
	 * 
	 * @param bit Bit "0" lub "1".
	 */
	void writeBit(bool bit) const;
	
	/**
	 * Wystawia bajt na magistrali.
	 * 
	 * @param byte Bajt.
	 */
	void writeByte(uint8_t byte) const;
	
	/**
	 * Odczytuje bit z magistrali.
	 * 
	 * @return Odczytany bit.
	 */
	bool readBit() const;
	
	/**
	 * Odczytuje bajt z magistrali.
	 * 
	 * @return Odczytany bajt.
	 */
	uint8_t readByte() const;
	
	/**
	 * Resetuje magistralę.
	 * 
	 * @return Czy ktokolwiek potwierdził reset?
	 */
	bool reset() const;
};
