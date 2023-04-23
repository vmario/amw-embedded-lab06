#include "thermostat.hpp"

#include <avr/io.h>

#define THERMOSTAT_HEATER_DDR DDRD ///< Rejestr kierunku elementu sterującego.
#define THERMOSTAT_HEATER_PORT PORTD ///< Rejestr wyjściowy elementu sterującego.
#define THERMOSTAT_HEATER_LED PD3 ///< Pin elementu sterującego.

Thermostat::Thermostat():
	targetTemperature{20.0}
{
	THERMOSTAT_HEATER_DDR |= _BV(THERMOSTAT_HEATER_LED);
}

double Thermostat::target() const
{
	return targetTemperature;
}

void Thermostat::target(double targetTemperature)
{
	this->targetTemperature = targetTemperature;
}

void Thermostat::onTemperature(double currentTemperature) const
{
}