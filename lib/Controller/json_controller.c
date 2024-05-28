#include "../JSON/readingObj/reading_t.h"
#include "../JSON/createJson/createJson.h"
#include "../JSON/cJSON.h"
#include "json_controller.h"
#include "connection_controller.h"
#include "water_flow_controller.h"
#include "sensor_controller.h"

#include <string.h>
#include <stdlib.h>
#include "AESHandler.h"
#include "key_exchange.h"

static char message_buffer[128];

char *create_json(reading *jsonInformation, int arraySize);

void json_controller_edit_output(uint8_t percentage) {
    water_flow_controller_set_flow(percentage);

    int arraySize = 1;
    reading information[arraySize];
    information[0] = (reading *)create_instances_in_json("status", 1);

      if (information == NULL) {
        pc_comm_send_string_blocking("Error creating JSON instances for status!\n");
        return;
    }

    char *temp = create_json(information, arraySize);

    if (temp == NULL) {
        pc_comm_send_string_blocking("Error creating JSON!\n");
        return;
    }

    int length = strlen(temp);

    connection_controller_transmit(temp, length);

    free(temp);
}

void json_controller_parse(char* pkg)
{
    cJSON *json = cJSON_Parse(pkg);

    if (json == NULL) {
        pc_comm_send_string_blocking("Error parsing JSON package!\n");
        return;
    }

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

        // ENCRYPTION
        //  else if (strcmp(cJSON_GetStringValue(requestType), "PublicKey") == 0)
        // {
        //     cJSON *key = cJSON_GetObjectItemCaseSensitive(json, "key");
        //     if (key != NULL && cJSON_IsString(key))
        //     {
                
        //         pc_comm_send_string_blocking("Received public key from server: ");
        //         pc_comm_send_string_blocking(cJSON_GetStringValue(key));
        //         pc_comm_send_string_blocking("\n");

        //          //check if key exchange is completed
        //         // if (!key_exchange_completed) {
        //         //     handle_received_public_key(cJSON_GetStringValue(key));
        //         // }
        //     }
        // }
    }

    cJSON_Delete(json); // frees memory
}


void json_controller_pkg() {
    int arraySize = 9;
    reading information[arraySize];

    uint8_t celc, hum;
    sensor_controller_dht11(&celc, &hum);

    // define each sensor, sadly manually :')
    information[0] = (reading *)create_instances_in_json("waterConductivity", sensor_controller_water_ec());
    information[1] = (reading *)create_instances_in_json("waterPh", sensor_controller_ph());
    information[2] = (reading *)create_instances_in_json("waterTemperature", sensor_controller_water_temp());
    information[3] = (reading *)create_instances_in_json("waterFlow", water_flow_controller_get_flow());
    information[4] = (reading *)create_instances_in_json("waterLevel", sensor_controller_water_temp());
    information[5] = (reading *)create_instances_in_json("airTemperature", celc);
    information[6] = (reading *)create_instances_in_json("airHumidity", hum);
    information[7] = (reading *)create_instances_in_json("lightLevel", sensor_controller_light());
    information[8] = (reading *)create_instances_in_json("airCo2", sensor_controller_co2());

    // this creates the json
    char *temp = create_json(information, arraySize);

    if (temp == NULL) {
        pc_comm_send_string_blocking("Error creating JSON!\n");
        return;
    }

    int length = strlen(temp);

    //encryption before transmiting
    // AESHandler_encrypt(&temp);

    connection_controller_transmit(temp, length);

    //Print confirmation of transmission
    pc_comm_send_string_blocking("JSON sent to server.\n");

    free(temp);
};
static void copy_key(char *buffer)
{
    strncpy(buffer, message_buffer + 6, 64); // + 6 because SK|64|
    buffer[64] = '\0';
}

void handle_received_public_key(const char *received_key) {
    
    char key[65]; //make space for null terminator
    copy_key(key);
    //generate shared secret using the received public key
    uint8_t shared_secret[17];
    key_exchange_generate_shared_secret((uint8_t *)key, shared_secret);
    
    AESHandler_init(shared_secret);

        key_exchange_completed = true;
}