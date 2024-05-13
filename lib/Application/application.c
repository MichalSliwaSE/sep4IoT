#include "application.h"
#include "connection_controller.h"
#include "dht11.h"
#include "display.h"
#include "pc_comm.h"
#include "wifi.h"
#include "connection_controller.h"
#include "json_controller.h"
#include "water_ec.h"
#include "ph_sensor.h"
#include "water_temperature.h"
#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

void serverCallback(char *buffer)
{
    pc_comm_send_string_blocking("Server >> ");
    pc_comm_send_string_blocking(buffer);
    pc_comm_send_string_blocking("\n");

    json_controller_parse(buffer);
}

void application_init() {
    pc_comm_init(9600, NULL);
    water_ec_init();
    ph_sensor_init();

    water_temperature_init();
    connection_controller_init(serverCallback);
};

void application_run() {
    pc_comm_send_string_blocking("Application running.\n");
};