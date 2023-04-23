#pragma once

/**
 * Sterownik debouncera impulsatora.
 */
struct EncoderDebouncer {
	/**
	 * Wyłącza przerwanie INT0 na 2^16 cykli zegara.
	 * 
	 * Flaga zgłoszenia przerwania jest czyszczona.
	 */
	void debounce() const;
};