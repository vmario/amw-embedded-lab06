#include "encoder.hpp"
#include "encoderDebouncer.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#define ENCODER_PIN PIND ///< Rejestr wejściowy impulsatora.
#define ENCODER_PORT PORTD ///< Rejestr wyjściowy impulsatora.
#define ENCODER_PIN_B PD1 ///< Pin B impulsatora.
#define ENCODER_PIN_SW PD4 ///< Pin przycisku impulsatora.

Encoder encoder;

/**
 * Obsługa przerwania INT0.
 */
ISR(INT0_vect)
{
#if 0
	EncoderDebouncer{}.debounce();
#endif
}

void Encoder::init() const
{
}

void Encoder::onClockwise()
{
}

void Encoder::onCounterClockwise()
{
}

int8_t Encoder::pop()
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
	}

	return 0;
}

bool Encoder::isSwitchPressed() const
{
	return false;
}