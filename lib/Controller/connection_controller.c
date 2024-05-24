#include "connection_controller.h"
#include "json_controller.h"
#include "pc_comm.h"
#include "wifi.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "includes.h"
#include <stdlib.h>
#include <string.h>
#include "../../env.h"
#include "key_exchange.h"
#include "AESHandler.h"


static void handle_key_exchange();

static char buffer[128];
static server_callback application_callback_function;


void connection_controller_callback() {
  application_callback_function(buffer);
}

bool connection_controller_init(server_callback callback) {
  _delay_ms(1000);
  bool result = false;
  application_callback_function = callback;
  wifi_init();

  WIFI_ERROR_MESSAGE_t connect_to_AP =
      wifi_command_join_AP(WIFI_SSID, WIFI_PASSWORD);
  char *server_ip = SERVER_IP;
  uint16_t server_port = SERVER_PORT;
  

  if (connect_to_AP == WIFI_OK) {
    pc_comm_send_string_blocking("Connected to AP!\n");
    WIFI_ERROR_MESSAGE_t connect_to_server =
        wifi_command_create_TCP_connection(server_ip, server_port, connection_controller_callback, buffer);

        handle_key_exchange();


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

  return true;
}

static void handle_key_exchange()
{
    uint8_t public_key[33];
    
    key_exchange_init();
    key_exchange_generate_keys();
    key_exchange_get_public_key(public_key);

    pc_comm_send_string_blocking("Sending public key to server:\n");
    pc_comm_send_string_blocking((char *)public_key); 

    connection_controller_transmit(public_key, sizeof(public_key));
}