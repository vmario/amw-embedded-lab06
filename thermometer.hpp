/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 *
 * Sterownik termometru.
 */

#pragma once

#include <stdint.h>

/**
 * Unikalny identyfikator termometru.
 */
struct RomCode {
	/**
	 * Tablica bajtów:
	 * 
	 * - 0 — Numer rodziny (0x28).
	 * - 1…6 — Numer seryjny.
	 * - 7 — CRC.
	 */
	uint8_t bytes[8];
};

/**
 * Sterownik termometru.
 */
struct Thermometer {
	/**
	 * Resetuje magistralę komunikacyjną.
	 * 
	 * @return Czy wykryto jakiekolwiek urządzenie?
	 */
	bool reset() const;
	
	/**
	 * Odczytuje identyfikator.
	 * 
	 * @return Odczytana ramka identyfikatora.
	 */
	RomCode romCode() const;

	/**
	 * Odczytuje temperaturę.
	 * 
	 * @return Odczytana temperatura.
	 */
	double temperature() const;
};
