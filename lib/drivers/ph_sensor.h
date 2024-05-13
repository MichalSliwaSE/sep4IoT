#pragma once
#include <stdint.h>

/// @brief Mock - Initializes the pH sensor and any necessary peripherals.
void ph_sensor_init(void);

/// @brief Mock - Simulates measuring the pH level of the water.
/// @return The simulated pH level measured.
uint16_t ph_sensor_measure(void);