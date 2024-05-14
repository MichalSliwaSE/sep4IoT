#pragma once
#include <inttypes.h>

/// @brief Mock - Initializes an array of random integers in a specified range, sorts them, and sets an initial value.
void water_ec_init(void);

/// @brief Measures the electrical conductivity of the water in microsiemens per centimeter. When measured, it moves either an index up or down depending on even/oddness of a random number.
uint16_t water_ec_measure(void);