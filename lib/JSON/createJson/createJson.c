#include "../readingObj/reading_t.h"
#include "createJson.h"
#include "../cJSON.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Reading_t *reading;

char *create_json(reading *jsonInformation, int arraySize)
{
    int readingCount = arraySize;
    char *string = NULL;
    cJSON *readings = NULL;
    size_t index = 0;

    cJSON *monitor = cJSON_CreateObject();

    if (cJSON_AddStringToObject(monitor, "name", "monitoring_results") == NULL)
    {
        goto end;
    }

    readings = cJSON_AddArrayToObject(monitor, "readings");
    if (readings == NULL)
    {
        goto end;
    }

    for (index = 0; index < readingCount; ++index)
    // for (index = 0; index < (sizeof(jsonInformation) / (2 * sizeof(int))); ++index)
    {
        cJSON *reading = cJSON_CreateObject();

        if (cJSON_AddNumberToObject(reading, jsonInformation[index]->name, jsonInformation[index]->reading) == NULL)
        {
            goto end;
        }

        cJSON_AddItemToArray(readings, reading);
    }

    string = cJSON_Print(monitor);
    if (string == NULL)
    {
        fprintf(stderr, "Failed to print monitor.\n");
    }

end:
    cJSON_Delete(monitor);
    for (index = 0; index < readingCount; ++index)
    // for (index = 0; index < (sizeof(jsonInformation) / sizeof(jsonInformation[0])); ++index)
    {
        free(jsonInformation[index]->name);
        free(jsonInformation[index]);
    }
    return string;
}