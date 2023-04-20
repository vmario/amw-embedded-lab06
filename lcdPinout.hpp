/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 *
 * Pinout wyświetlacza LCD.
 */

#include <avr/io.h>

#define LCD_RS_DIR DDRA
#define LCD_RS_PORT PORTA
#define LCD_RS _BV(PA0)

#define LCD_E_DIR DDRA
#define LCD_E_PORT PORTA
#define LCD_E _BV(PA2)

#define LCD_DB_DIR DDRA
#define LCD_DB_PORT PORTA
#define LCD_DB_OFFSET PA3
