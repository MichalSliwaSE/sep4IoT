#pragma once
#include <inttypes.h>

void sensor_controller_init();

void sensor_controller_dht11(uint8_t *celc, uint8_t *hum);

int sensor_controller_water_ec();

int sensor_controller_ph();

int sensor_controller_water_temp();

int sensor_controller_water_level();

int sensor_controller_light();

int sensor_controller_co2();

void sensor_controller_send(char *string);