#include "../JSON/readingObj/reading_t.h"
#include "../JSON/createJson/createJson.h"
#include "../JSON/cJSON.h"
#include "json_controller.h"
#include "water_ec.h"
#include "ph_sensor.h"
#include "water_temperature.h"
#include "connection_controller.h"
#include <string.h>
#include <stdlib.h>
#include "pc_comm.h"

char *create_json(reading *jsonInformation, int arraySize);

void json_controller_parse(char* pkg)
{
    cJSON *json = cJSON_Parse(pkg);
    cJSON *requestType;

    requestType = cJSON_GetObjectItemCaseSensitive(json, "requestType");

    if ((requestType->valuestring != NULL) && cJSON_IsString(requestType))
    {
        if (strcmp(cJSON_GetStringValue(requestType), "Request") == 0)
        {
            json_controller_pkg();
        }
    }

    cJSON_Delete(json); //frees memory
};

void json_controller_pkg() {
    int arraySize = 3;
    reading information[arraySize];

    // define each sensor, sadly manually :')
    information[0] = (reading *)create_instances_in_json("water_conductivity", water_ec_measure());
    information[1] = (reading *)create_instances_in_json("water_ph", ph_sensor_measure());
    information[2] = (reading *)create_instances_in_json("water_temperature", water_temperature_get());

    // this creates the json
    char *temp = create_json(information, arraySize);
    int length = strlen(temp);

    connection_controller_transmit(temp, length);

    free(temp);
};