#include "connection_controller.h"
#include "dht11.h"
#include "display.h"
#include "pc_comm.h"
#include "wifi.h"
#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h> 

// Callback function to handle server events
void serverCallback(char *buffer) {

  // Convert the received string to an integer
    int16_t value = atoi(buffer);
    display_int(value);
   // Send the received data to the PC
    pc_comm_send_string_blocking("Received data from server: ");
    pc_comm_send_string_blocking(buffer);
    pc_comm_send_string_blocking("\n");
}

int main() {
    display_init();
    pc_comm_init(9600, NULL);

    while (1) {
        connection_controller_init(serverCallback);
        connection_controller_transmit("Hello World!", 13);
        // Add a delay to avoid overwhelming the system with repeated attempts
        _delay_ms(1000); // Adjust the delay time as needed
    }

    return 0;
}
