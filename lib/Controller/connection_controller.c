#include "connection_controller.h"
#include "pc_comm.h"
#include "wifi.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "includes.h"

// Define parameters for the first configuration block
#define WIFI_SSID_1 "Fibernet-IA02592142"
#define WIFI_PASSWORD_1 ""
#define SERVER_IP_1 ""
#define SERVER_PORT_1 23

// Define parameters for the second configuration block
#define WIFI_SSID_2 ""
#define WIFI_PASSWORD_2 ""
#define SERVER_IP_2 ""
#define SERVER_PORT_2 23

// Define parameters for the third configuration block
#define WIFI_SSID_3 ""
#define WIFI_PASSWORD_3 ""
#define SERVER_IP_3 ""
#define SERVER_PORT_3 23

// Uncomment to select the desired configuration block
#define USE_CONFIG_BLOCK_1
// #define USE_CONFIG_BLOCK_2
//#define USE_CONFIG_BLOCK_3

static char buffer[25];
static server_callback application_callback_function;

void connection_control_callback() {
  application_callback_function(buffer);
}


bool connection_controller_init(server_callback callback) {
  _delay_ms(1000);
  bool result = false;
  application_callback_function = callback;
  wifi_init();

  #if defined(USE_CONFIG_BLOCK_1)
    WIFI_ERROR_MESSAGE_t connect_to_AP =
        wifi_command_join_AP(WIFI_SSID_1, WIFI_PASSWORD_1);
    const char *server_ip = SERVER_IP_1;
    const uint16_t server_port = SERVER_PORT_1;
  #elif defined(USE_CONFIG_BLOCK_2)
    WIFI_ERROR_MESSAGE_t connect_to_AP =
        wifi_command_join_AP(WIFI_SSID_2, WIFI_PASSWORD_2);
    const char *server_ip = SERVER_IP_2;
    const uint16_t server_port = SERVER_PORT_2;
  #elif defined(USE_CONFIG_BLOCK_3)
    WIFI_ERROR_MESSAGE_t connect_to_AP =
        wifi_command_join_AP(WIFI_SSID_3, WIFI_PASSWORD_3);
    const char *server_ip = SERVER_IP_3;
    const uint16_t server_port = SERVER_PORT_3;
  #else
    #error "No configuration block selected!"
  #endif

  if (connect_to_AP == WIFI_OK) {
    pc_comm_send_string_blocking("Connected to AP!\n");
    WIFI_ERROR_MESSAGE_t connect_to_server =
        wifi_command_create_TCP_connection(server_ip, server_port, connection_control_callback, buffer);
    if (connect_to_server == WIFI_OK) {
      pc_comm_send_string_blocking("Connected to server!\n");
      result = true;
    } else {
      result = false;
      pc_comm_send_string_blocking("Error connecting to server!\n");
    }
  } else {
    result = false;
    pc_comm_send_string_blocking("Error connecting to Wifi AP!\n");
  }

  return result;
}

bool connection_controller_transmit(char *package, int length) {
  wifi_command_TCP_transmit(package, length);
}
