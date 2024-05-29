#include "sensor_controller.h"
#include "connection_controller.h"
#include "dht11.h"
#include "pc_comm.h"
#include "wifi.h"
#include "connection_controller.h"
#include "json_controller.h"
#include "water_ec.h"
#include "ph_sensor.h"
#include "water_temperature.h"
#include "water_level.h"
#include "light.h"
#include "co2.h"
#include "pc_comm.h"

void sensor_controller_init() {
    pc_comm_init(9600, NULL);
    water_ec_init();
    ph_sensor_init();
    dht11_init();
    light_init();
    co2_init();

    water_temperature_init();
    water_level_init();
}

void sensor_controller_dht11(uint8_t *celc, uint8_t *hum)
{
    dht11_get(hum, NULL, celc, NULL);
};

int sensor_controller_water_ec()
{
    return water_ec_measure();
};

int sensor_controller_ph()
{
    return ph_sensor_measure();
};

int sensor_controller_water_temp()
{
    return water_temperature_get();
};

int sensor_controller_water_level()
{
    return water_level_measure();
};

int sensor_controller_light()
{
    return light_read();
};

int sensor_controller_co2()
{
    return co2_measure();
};

void sensor_controller_send(char *string)
{
    pc_comm_send_string_blocking(string);
};

