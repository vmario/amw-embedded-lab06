/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 *
 * Implementacja sterowania wyświetlaczem LCD.
 */

#include "lcd.hpp"

#include "lcdDriver.hpp"
#include "lcdCommands.hpp"

void Lcd::clear() const
{
	CommandClear().write();
}

void Lcd::write(char symbol) const
{
	Data(symbol).write();
}

void Lcd::write(const char* text) const
{
	while (*text) {
		Data(*text++).write();
	}
}

void Lcd::goTo(uint8_t line, uint8_t column) const
{
	CommandSetDdramAddress(line, column).write();
}

void Lcd::init() const
{
	const Driver driver;
	driver.initGpio();
	driver.initLogic();
	driver.init4Bit();
	
	CommandFunctionSet(FUNCTION_SET_OPTION_DUAL_LINE).write();
	CommandDisplayControl().write();
	CommandClear().write();
	CommandEntryMode(ENTRY_MODE_OPTION_INCREMENT).write();
	CommandDisplayControl(DISPLAY_CONTROL_OPTION_DISPLAY_ON).write();
}