/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 * 
 * Implementacja komend sterujących wyświetlaczem.
 */

#include "lcdCommands.hpp"

#include <util/delay.h>

void CommandClear::write() const
{
	command.write();
	_delay_ms(1.52);
}

void CommandEntryMode::write() const
{
	command.write();
	_delay_us(37);
}

void CommandDisplayControl::write() const
{
	command.write();
	_delay_us(37);
}

void CommandFunctionSet::write() const
{
	command.write();
	_delay_us(37);
}

void CommandSetDdramAddress::write() const
{
	command.write();
	_delay_us(37);
}
