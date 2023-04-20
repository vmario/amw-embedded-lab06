/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 * 
 * Pętla główna.
 */

#include "lcd.hpp"
#include "timer.hpp"
#include "thermometer.hpp"

#include <stdlib.h>
#include <stdio.h>

/**
 * Wyświetla komunikat powitalny.
 */
static void lcdSplash(const Lcd& lcd)
{
	lcd.clear();
	lcd.write("Initializing...");
}

/**
 * Wyświetla numer seryjny termometru.
 * 
 * @param lcd Sterownik LCD.
 */
static void printSerialNumber(const Lcd& lcd)
{
	RomCode romCode{Thermometer{}.romCode()};
	char buffer[17] = "0x";
	for (uint8_t i{0}; i < 7; ++i) {
		snprintf(buffer + 2 + 2 * i, 3, "%02x", romCode.bytes[i]);
	}
	lcd.write(buffer);
}

/**
 * Wyświetla temperaturę.
 * 
 * @param lcd Sterownik LCD.
 */
static void printTemperature(const Lcd& lcd)
{
	char buffer[17];
	snprintf(buffer, sizeof(buffer), "T=%6.2f", Thermometer{}.temperature());
	lcd.write(buffer);
}

/**
 * Wyświetla pomiar temperatury.
 * 
 * @param lcd Sterownik LCD.
 */
static void lcdRefresh(const Lcd& lcd)
{
	if (!Thermometer{}.reset()) {
		lcd.clear();
		lcd.write("1-Wire Error :( ");
		return;
	}

	lcd.goTo(0, 0);
	printSerialNumber(lcd);
	lcd.goTo(1, 0);
	printTemperature(lcd);
}

/**
 * Funkcja główna.
 */
int main()
{
	const Lcd lcd;
	const SystemTick tick;

	lcd.init();
	tick.init();
	lcdSplash(lcd);

	while (true) {
		if (tick.checkAndClear()) {
			lcdRefresh(lcd);
		}
	}

	return EXIT_SUCCESS;
}