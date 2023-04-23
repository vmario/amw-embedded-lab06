/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 *
 * Implementacja sterownika termometru.
 */

#include "thermometer.hpp"

#include "1wire.hpp"

/**
 * Komendy 1Wire termometru.
 */
enum COMMAND {
	COMMAND_READ_ROM = 0x33, ///< Odczyt identyfikatora.
	COMMAND_CONVERT_T = 0x44, ///< Uruchamia pomiar temperatury.
	COMMAND_READ_SCRATCHPAD = 0xBE, ///< Odczytuje wynik pomiaru.
	COMMAND_SKIP_ROM = 0xCC, ///< Adresuje jedyny slave na magistrali.
};

bool Thermometer::reset() const
{
	const Wire1 bus{};

	return bus.reset();
}

RomCode Thermometer::romCode() const
{
	const Wire1 bus{};
	RomCode romCode;

	bus.writeByte(COMMAND_READ_ROM);

	for (uint8_t i{0}; i < sizeof(romCode.bytes); ++i) {
		romCode.bytes[i] = bus.readByte();
	}

	return romCode;
}

double Thermometer::temperature() const
{
	const Wire1 bus{};

	bus.reset();
	bus.writeByte(COMMAND_SKIP_ROM);
	bus.writeByte(COMMAND_CONVERT_T);

	bus.reset();
	bus.writeByte(COMMAND_SKIP_ROM);
	bus.writeByte(COMMAND_READ_SCRATCHPAD);

	return 1.0 * (bus.readByte() | (bus.readByte() << 8)) / 16;
}