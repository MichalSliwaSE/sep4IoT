#pragma once
#include <inttypes.h>

void water_ec_init(void);

/// @brief Measures the electrical conductivity of the water in microsiemens per centimeter.
uint16_t water_ec_measure(void);