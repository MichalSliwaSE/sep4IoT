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
#include "AESHandler.h"
#include "key_exchange.h"

static char message_buffer[128];

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
        else if (strcmp(cJSON_GetStringValue(requestType), "PublicKey") == 0)
        {
            cJSON *key = cJSON_GetObjectItemCaseSensitive(json, "key");
            if (key != NULL && cJSON_IsString(key))
            {
                
                pc_comm_send_string_blocking("Received public key from server: ");
                pc_comm_send_string_blocking(cJSON_GetStringValue(key));
                pc_comm_send_string_blocking("\n");

                 //check if key exchange is completed
                if (!key_exchange_completed) {
                    handle_received_public_key(cJSON_GetStringValue(key));
                }
            }
        }
    }

    cJSON_Delete(json); // frees memory
}


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
    //encryption before transmiting
    AESHandler_encrypt(&temp);

    connection_controller_transmit(temp, length);

    free(temp);
}

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