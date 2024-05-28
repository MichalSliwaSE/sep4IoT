#include "application.h"
#include "sensor_controller.h"
#include "connection_controller.h"
#include "json_controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "key_exchange.h"
#include "AESHandler.h"


void serverCallback(char *buffer)
{
     if (buffer == NULL) {
        sensor_controller_send("Error: Received null buffer from server!\n");
        return;
    }
    sensor_controller_send("Server >> ");
    sensor_controller_send(buffer);
    sensor_controller_send("\n");

    if (key_exchange_completed) {
        AESHandler_decrypt(buffer);
    }

    json_controller_parse(buffer);
}

void application_init() {
    sensor_controller_init();
    connection_controller_init(serverCallback);
}

void application_run() {
    sensor_controller_send("Application running.\n");
};