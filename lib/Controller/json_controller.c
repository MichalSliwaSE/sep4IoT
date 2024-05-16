#include "../JSON/readingObj/reading_t.h"
#include "../JSON/createJson/createJson.h"
#include "../JSON/cJSON.h"
#include "json_controller.h"
#include "water_ec.h"
#include "ph_sensor.h"
#include "water_temperature.h"
#include "dht11.h"
#include "connection_controller.h"
#include "water_flow_controller.h"
#include "water_level.h"
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

        else if (strcmp(cJSON_GetStringValue(requestType), "waterFlowCorrection") == 0)
        {
            cJSON *outputValue;
            outputValue = cJSON_GetObjectItemCaseSensitive(json, "value");

            double dValue;
            dValue = cJSON_GetNumberValue(outputValue);

            uint8_t value;

            if (dValue < 0)
            value = 0;
            else if (dValue > 255)
            value = 255;
            else
            value = (uint8_t)dValue;

            json_controller_edit_output(value);
        }
    }

    cJSON_Delete(json); //frees memory
};

void json_controller_pkg() {
    int arraySize = 7;
    reading information[arraySize];

    uint8_t celc, hum_int;
    dht11_get(&hum_int, NULL, &celc, NULL);

    // define each sensor, sadly manually :')
    information[0] = (reading *)create_instances_in_json("water_conductivity", water_ec_measure());
    information[1] = (reading *)create_instances_in_json("water_ph", ph_sensor_measure());
    information[2] = (reading *)create_instances_in_json("water_temperature", water_temperature_get());
    information[3] = (reading *)create_instances_in_json("water_flow_rate", water_flow_controller_get_flow());
    information[4] = (reading *)create_instances_in_json("water_level", water_level_measure());
    information[5] = (reading *)create_instances_in_json("temperature", celc);
    information[6] = (reading *)create_instances_in_json("humidity", hum_int);

    // this creates the json
    char *temp = create_json(information, arraySize);
    int length = strlen(temp);

    connection_controller_transmit(temp, length);

    free(temp);
};

void json_controller_edit_output(uint8_t percentage) {
    water_flow_controller_set_flow(percentage);

    int arraySize = 1;
    reading information[arraySize];
    information[0] = (reading *)create_instances_in_json("status", 1);

    char *temp = create_json(information, arraySize);
    int length = strlen(temp);

    connection_controller_transmit(temp, length);

    free(temp);
}