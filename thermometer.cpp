/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 *
 * Implementacja sterownika termometru.
 */

#include "thermometer.hpp"

#include "1wire.hpp"

bool Thermometer::reset() const
{
	const Wire1 bus{};

	return bus.reset();
}

RomCode Thermometer::romCode() const
{
	RomCode romCode = { { 0 } };

	return romCode;
}

double Thermometer::temperature() const
{
	return 0;
}