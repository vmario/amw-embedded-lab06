/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 * 
 * Komendy sterujące wyświetlaczem.
 */

#pragma once

#include "lcdDriver.hpp"

/**
 * Opcje komendy Entry Mode.
 */
enum ENTRY_MODE_OPTION {
	ENTRY_MODE_OPTION_INCREMENT = 0x02, ///< Inkrementacja adresacji.
};

/**
 * Opcje komendy Display Control.
 */
enum DISPLAY_CONTROL_OPTION {
	DISPLAY_CONTROL_OPTION_CURSOR_BLINK = 0x01, ///< Mrugający kursor.
	DISPLAY_CONTROL_OPTION_CURSOR_ON = 0x02, ///< Widoczny kursors.
	DISPLAY_CONTROL_OPTION_DISPLAY_ON = 0x04, ///< Wyświetlacz włączony.
};

/**
 * Opcje komendy Function Set.
 */
enum FUNCTION_SET_OPTION {
	FUNCTION_SET_OPTION_DUAL_LINE = 0x08, ///< Wyświetlacz z dwoma liniami tekstu.
};

/**
 * Czyści wyświetlacz.
 */
struct CommandClear {
	/**
	 * Konstruktor.
	 */
	CommandClear():
		command{0x01}
	{}
	
	void write() const; ///< Wysyła komendę do wyświetlacza.
	
private:
	const Command command; ///< Komenda z przypisanymi opcjami.
};

/**
 * Ustawia tryb adresacji.
 */
struct CommandEntryMode {
	/**
	 * Konstruktor.
	 *
	 * @param options Opcje komendy.
	 */
	CommandEntryMode(uint8_t options=0):
		command{static_cast<uint8_t>(0x04 | (options & 0x03))}
	{}
	
	void write() const; ///< Wysyła komendę do wyświetlacza.

private:
	const Command command; ///< Komenda z przypisanymi opcjami.
};

/**
 * Włącza wyświetlacz i kursor.
 */
struct CommandDisplayControl {
	/**
	 * Konstruktor.
	 *
	 * @param options Opcje komendy.
	 */
	CommandDisplayControl(uint8_t options=0):
		command{static_cast<uint8_t>(0x08 | (options & 0x07))}
	{}
	
	void write() const; ///< Wysyła komendę do wyświetlacza.

private:
	const Command command; ///< Komenda z przypisanymi opcjami.
};

/**
 * Konfiguracja funkcji.
 */
struct CommandFunctionSet {
	/**
	 * Konstruktor.
	 *
	 * @param options Opcje komendy.
	 */
	CommandFunctionSet(uint8_t options=0):
		command{static_cast<uint8_t>(0x20 | (options & 0x1c))}
	{}
	
	void write() const; ///< Wysyła komendę do wyświetlacza.

private:
	const Command command; ///< Komenda z przypisanymi opcjami.
};

/**
 * Ustawia adres DDRAM (pozycję kursora).
 */
struct CommandSetDdramAddress {
	/**
	 * Konstruktor.
	 *
	 * @param line Numer linii.
	 * @param column Numer kolumny.
	 */
	CommandSetDdramAddress(uint8_t line, uint8_t column):
		command{static_cast<uint8_t>(0x80 | ((line * 0x40 + column) & 0x7f))}
	{}
	
	void write() const; ///< Wysyła komendę do wyświetlacza.

private:
	const Command command; ///< Komenda z przypisanymi opcjami.
};

