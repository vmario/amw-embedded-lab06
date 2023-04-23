#include "encoderDebouncer.hpp"

#include <avr/interrupt.h>
#include <util/atomic.h>

/**
 * Obsługa przerwania przepełnienia timera 1.
 */
ISR(TIMER1_OVF_vect)
{
	TIMSK1 &= ~_BV(TOIE1);
	TCCR1B = 0;
	EIFR |= INTF0;
	EIMSK |= _BV(INT0);
}

void EncoderDebouncer::debounce() const
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		EIMSK &= ~_BV(INT0);
		TCNT1 = 0x0000;
		TCCR1B = _BV(CS10);
		TIMSK1 = _BV(TOIE1);
	}
}