/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 * 
 * Implementacja przerwania od timera.
 */

#include "timer.hpp"

#include "lcd.hpp"

#include <avr/interrupt.h>
#include <util/atomic.h>

/**
 * Konfiguracja Timer/Counter0 w trybie Clear Timer on Compare Match.
 */
static constexpr uint8_t TIMER0_CTC = _BV(WGM01);

/**
 * Taktowanie Timer/Counter0 zegarem podzielonym przez 256.
 */
static constexpr uint8_t TIMER0_PRESCALER_256 = _BV(CS02);

/**
 * Rejestr komparatora Timer/Counter0 dający tick 125Hz.
 */
static constexpr uint8_t TIMER0_OCR_TICK = 250;

/**
 * Liczba ticków timera, co ile występuje tick systemowy 1Hz.
 */
static constexpr uint8_t SYSTEM_TICK_INTERVAL = 125;

static volatile bool expired; ///< Czy timer ustawił flagę?

/**
 * Obsługa przerwania TIMER0_COMPA.
 */
ISR(TIMER0_COMPA_vect)
{
	static uint32_t interval;
	if (++interval > SYSTEM_TICK_INTERVAL) {
		interval = 0;
		expired = true;
	}
}

void SystemTick::init() const
{
	TCCR0A = TIMER0_CTC;
	TCCR0B = TIMER0_PRESCALER_256;
	OCR0A = TIMER0_OCR_TICK;
	TIMSK0 = _BV(OCIE0A);
}

bool SystemTick::pop() const
{
	bool status;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		status = expired;
		if (status) {
			expired = false;
		}
	}
	
	return status;
}