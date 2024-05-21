#pragma once
#include <inttypes.h>

/// @brief Mock - Initializes a starting water level value.
void water_level_init(void);

/// @brief Measures the water level in arbitrary units. Returns a value close to the last measurement.
uint16_t water_level_measure(void);
