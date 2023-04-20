/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 *
 * Sterowanie wyświetlaczem LCD.
 */

#pragma once

#include <stdint.h>

/**
 * Sterownik wyświetlacza, korzystający ze sterownika Hitachi HD44780.
 * 
 * Zapis następuje na pozycji, w której aktualnie znajduje się kursor.
 */
struct Lcd {
	/**
	 * Inicjalizuje wyświetlacz.
	 */
	void init() const;
	
	/**
	 * Czyści wyświetlacz.
	 */
	void clear() const;

	/**
	 * Zapisuje symbol na wyświetlaczu.
	 * 
	 * @param symbol Symbol do zapisania.
	 */
	void write(char symbol) const;

	/**
	 * Zapisuje tekst na wyświetlaczu.
	 * 
	 * @param symbol Tekst do zapisania.
	 */
	void write(const char* text) const;
	
	/**
	 * Ustawia kursor na wskazanej pozycji.
	 * 
	 * @param line Numer linii.
	 * @param column Numer kolumny.
	 */
	void goTo(uint8_t line, uint8_t column) const;
};
