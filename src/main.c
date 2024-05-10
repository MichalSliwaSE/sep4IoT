// #include "connection_controller.h"
// #include "dht11.h"
// #include "display.h"
#include "pc_comm.h"
// #include "wifi.h"
#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>

// json imports from the lib and method reference
#include "../lib/JSON/readingObj/reading_t.h"
#include "../lib/JSON/createJson/createJson.h"
char *create_json(reading *jsonInformation, int arraySize);

// // Callback function to handle server events
// void serverCallback(char *buffer)
// {

//     // Convert the received string to an integer
//     int16_t value = atoi(buffer);
//     display_int(value);
//     // Send the received data to the PC
//     pc_comm_send_string_blocking("Received data from server: ");
//     pc_comm_send_string_blocking(buffer);
//     pc_comm_send_string_blocking("\n");
// }

int main()
{
    // display_init();
    // pc_comm_init(9600, NULL);

    // while (1)
    // {
    //     connection_controller_init(serverCallback);
    //     connection_controller_transmit("Hello World!", 13);
    //     // Add a delay to avoid overwhelming the system with repeated attempts
    //     _delay_ms(1000); // Adjust the delay time as needed
    // }

    pc_comm_init(9600, NULL);



    // how to use the json in the main or generally if we need to put it in a different class
    int arraySize = 3;
    reading *informatoin[arraySize];

    // define each sensor, sadly manually :')
    informatoin[0] = create_instances_in_json("Electricity", 1);
    informatoin[1] = create_instances_in_json("Dampness", 2);
    informatoin[2] = create_instances_in_json("Watter pressure", 3);

    // this creates the json
    char *temp = create_json(informatoin, arraySize);

    pc_comm_send_string_blocking(temp);

    // this prints it out if it didnt return null at some point in time AND frees up the memory it was using
    if (temp != NULL)
    {
        printf("JSON Object:\n%s\n", temp);

        free(temp); // Free the string returned by create_monitor_with_helpers
    }
    return 0;
}
