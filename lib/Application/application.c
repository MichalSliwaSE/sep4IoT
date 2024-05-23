#include "application.h"
#include "sensor_controller.h"
#include "connection_controller.h"
#include "json_controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void serverCallback(char *buffer)
{
    sensor_controller_send("Server >> ");
    sensor_controller_send(buffer);
    sensor_controller_send("\n");

    json_controller_parse(buffer);
}

void application_init() {
    sensor_controller_init();
    connection_controller_init(serverCallback);
};

void application_run() {
    sensor_controller_send("Application running.\n");
};