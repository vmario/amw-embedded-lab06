/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 *
 * Pinout magistrali 1-Wire.
 */

#pragma once

#include <avr/io.h>

#define WIRE_1_DIR DDRC ///< Rejestr kierunku.
#define WIRE_1_PIN PINC ///< Rejestr wejściowy.
#define WIRE_1_DATA _BV(PC0) ///< Maska pinu danych.
