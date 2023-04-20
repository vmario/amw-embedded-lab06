/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 *
 * Sterownik wyświetlacza alfanumerycznego Hitachi HD44780.
 * 
 * Pinout należy zdefiniować w pliku lcdPinout.hpp.
 */

#pragma once

#include <stdint.h>

constexpr uint8_t NIBBLE_MASK{0x0f}; ///< Maska półbajtu.

/**
 * Półbajt wysyłany na szynę komunikacyjną.
 */
struct Nibble {
	/**
	 * Konstruktor.
	 *
	 * @param value Wartość półbajtu.
	 */
	Nibble(uint8_t value):
		value{static_cast<uint8_t>(value & NIBBLE_MASK)}
	{}
	
	void write() const; ///< Wysyła półbajt do wyświetlacza.

private:
	const uint8_t value; ///< Wartość półbajtu.
};

/**
 * Bajt wysyłany na szynę komunikacyjną w postaci dwóch półbajtów.
 */
struct Byte {
	/**
	 * Konstruktor.
	 *
	 * @param value Wartość bajtu.
	 */
	Byte(uint8_t value):
		value{value}
	{}
	
	void write() const; ///< Wysyła bajt do wyświetlacza.

private:
	const uint8_t value; ///< Wartość bajtu.
};

/**
 * Komenda wysyłana do wyświetlacza.
 */
struct Command {
	/**
	 * Konstruktor.
	 *
	 * @param value Komenda wraz z opcjami.
	 */
	Command(uint8_t value):
		value{value}
	{}
	
	void write() const; ///< Wysyła komendę do wyświetlacza.

private:
	const uint8_t value; ///< Komenda do wysłania.
};

/**
 * Dane (symbol) wysyłany do wyświetlacza.
 */
struct Data {
	/**
	 * Konstruktor.
	 *
	 * @param value Dane.
	 */
	Data(uint8_t value):
		value{value}
	{}
	
	void write() const; ///< Wysyła dane do wyświetlacza.

private:
	const uint8_t value; ///< Symbol do wysłania.
};

/**
 * Sterownik wyświetlacza Hitachi HD44780.
 * 
 * Obsługuje wyświetlacz w trybie 4-bitowym bez odczytu statusu.
 * 
 * @warning Wysyłanie komend obejmuje odmierzanie czasu potrzebnego na przetworzenie
 * komendy przez kontroler LCD.
 */
struct Driver {
	void initGpio() const; ///< Inicjalizuje GPIO uC.
	void initLogic() const; ///< Sekwencja uruchomieniowa sterownika.
	void init4Bit() const; ///< Przełączenie interfejsu w tryb 4-bitowy.
};
