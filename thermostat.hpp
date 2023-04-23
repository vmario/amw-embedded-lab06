#pragma once

/**
 * Sterownik termostatu.
 */
struct Thermostat {
	/**
	 * Konstruktor.
	 */
	Thermostat();

	/**
	 * Odczytuje zadaną temperaturę.
	 */
	double target() const;

	/**
	 * Ustawia zadaną temperaturę.
	 */
	void target(double targetTemperature);

	/**
	 * Zdarzenie odczytu temperatury.
	 * 
	 * W reakcji na zmianę tempeatury grzałka jest włączana lub wyłączana.
	 */
	void onTemperature(double currentTemperature) const;

private:
	double targetTemperature; ///< Zadana temperatura.
};