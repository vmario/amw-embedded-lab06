/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 *
 * Implementacja sterownika wyświetlacza alfanumerycznego Hitachi HD44780.
 */

#include "lcdDriver.hpp"

#include "lcdPinout.hpp"

#include <util/delay.h>

/**
 * Parametry interfejsu komunikacyjnego.
 */
enum INTERFACE_LENGTH {
	INTERFACE_LENGTH_4BIT = 0x02, ///< Interfejs 4-bitowy.
	INTERFACE_LENGTH_8BIT = 0x03, ///< Interfejs 8-bitowy.
};

void Nibble::write() const
{
	constexpr uint8_t LCD_DB_PORT_MASK = ~(NIBBLE_MASK << LCD_DB_OFFSET);

	LCD_E_PORT |= LCD_E;
	LCD_DB_PORT = (value << LCD_DB_OFFSET) | (LCD_DB_PORT & LCD_DB_PORT_MASK);
	_delay_us(1);
	LCD_E_PORT &= ~LCD_E;
	_delay_us(1);
}

void Byte::write() const
{
	Nibble(value >> 4).write();
	Nibble(value).write();
}

void Command::write() const
{
	LCD_RS_PORT &= ~LCD_RS;
	Byte(value).write();
}

void Data::write() const
{
	LCD_RS_PORT |= LCD_RS;
	Byte(value).write();
	_delay_us(37);
}

void Driver::initGpio() const
{
	LCD_DB_DIR |= NIBBLE_MASK << LCD_DB_OFFSET;
	LCD_E_DIR |= LCD_E;
	LCD_RS_DIR |= LCD_RS;
}

void Driver::initLogic() const
{
	_delay_ms(40);
	Nibble(INTERFACE_LENGTH_8BIT).write();
	_delay_us(4100);
	Nibble(INTERFACE_LENGTH_8BIT).write();
	_delay_us(100);
	Nibble(INTERFACE_LENGTH_8BIT).write();
	_delay_us(37);
}

void Driver::init4Bit() const
{
	Nibble(INTERFACE_LENGTH_4BIT).write();
	_delay_ms(37);
}
