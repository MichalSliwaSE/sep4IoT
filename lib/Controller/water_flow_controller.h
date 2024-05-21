#pragma once
#include <stdint.h>

void water_flow_controller_init();

void water_flow_controller_set_flow(uint8_t percentage);

uint8_t water_flow_controller_get_flow();