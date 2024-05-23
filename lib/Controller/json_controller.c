#include "../JSON/readingObj/reading_t.h"
#include "../JSON/createJson/createJson.h"
#include "../JSON/cJSON.h"
#include "json_controller.h"
#include "connection_controller.h"
#include "water_flow_controller.h"
#include "sensor_controller.h"

#include <string.h>
#include <stdlib.h>

char *create_json(reading *jsonInformation, int arraySize);

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
    int arraySize = 9;
    reading information[arraySize];

    uint8_t celc, hum;
    sensor_controller_dht11(&celc, &hum);

    // define each sensor, sadly manually :')
    information[0] = (reading *)create_instances_in_json("water_conductivity", sensor_controller_water_ec());
    information[1] = (reading *)create_instances_in_json("water_ph", sensor_controller_ph());
    information[2] = (reading *)create_instances_in_json("water_temperature", sensor_controller_water_temp());
    information[3] = (reading *)create_instances_in_json("water_flow_rate", water_flow_controller_get_flow());
    information[4] = (reading *)create_instances_in_json("water_level", sensor_controller_water_temp());
    information[5] = (reading *)create_instances_in_json("temperature", celc);
    information[6] = (reading *)create_instances_in_json("humidity", hum);
    information[7] = (reading *)create_instances_in_json("light", sensor_controller_light());
    information[8] = (reading *)create_instances_in_json("co2", sensor_controller_co2());

    // this creates the json
    char *temp = create_json(information, arraySize);
    int length = strlen(temp);

    connection_controller_transmit(temp, length);

    free(temp);
};
