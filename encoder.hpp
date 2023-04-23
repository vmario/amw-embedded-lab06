#pragma once

#include <stdint.h>

/**
 * Sterownik impulsatora.
 */
struct Encoder {
	
	/**
	 * Konstruktor.
	 * 
	 * Zeruje liczbę impulsów.
	 */
	Encoder():
		pulses{}
	{}

	/**
	 * Inicjalizuje GPIO i przerwania potrzebne do działania impulsatora.
	 */
	void init() const;

	/**
	 * Zdarzenie generowanie po jednym kroku w kierunku CW.
	 */
	void onClockwise();

	/**
	 * Zdarzenie generowanie po jednym kroku w kierunku CCW.
	 */
	void onCounterClockwise();
	
	/**
	 * Odczytuje zliczone dotąd impulsy i zeruje je.
	 */
	int8_t pop();
	
	/**
	 * Sprawdza, czy przycisk impulsatora jest wciśnięty.
	 */
	bool isSwitchPressed() const;

private:
	int8_t pulses; ///< Impulsy zliczone od ostatniego wywołania pop().
};

/**
 * Impulsator obsługiwany przez system na przerwaniu INT0.
 */
extern Encoder encoder;