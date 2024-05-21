#include "connection_controller.h"
#include "json_controller.h"
#include "pc_comm.h"
#include "wifi.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "includes.h"
#include <stdlib.h>
#include <string.h>
#include "../../env.h"
#include "aes.h"
#include "crypto_setup.h"
#include "key_exchange.h"

// AES context
struct AES_ctx ctx;

static char buffer[100];
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
    if (connect_to_server == WIFI_OK) {
      pc_comm_send_string_blocking("Connected to server!\n");

       // Initialize key exchange and share public key
      initialize_key_exchange();
      pc_comm_send_string_blocking("Key exchange initialized!\n");


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
    // Ensure the length is a multiple of 16 for AES encryption
    int padded_length = length;
    if (length % 16 != 0) {
        padded_length = ((length / 16) + 1) * 16;
    }

    uint8_t encrypted_package[padded_length];
    memset(encrypted_package, 0, padded_length);
    memcpy(encrypted_package, package, length);

    // Encrypt the package
    AES_ECB_encrypt(&ctx, encrypted_package);

    // Transmit the encrypted data
    wifi_command_TCP_transmit((char *)encrypted_package, padded_length);

    return true;
}
void on_receive_server_public_key(uint8_t *server_public_key) {
    uint8_t shared_secret[17]; // 16 bytes for AES key + 1 for null terminator
    key_exchange_generate_shared_secret(server_public_key, shared_secret);

    // Now, the shared_secret is your AES key
    AES_init_ctx(&ctx, shared_secret); // Initialize AES context with the shared secret
}
void on_receive_data(uint8_t *encrypted_data, int length) {
    // Ensure the length is a multiple of 16 for AES decryption
    if (length % 16 != 0) {
        // Handle error: length should be a multiple of 16
        return;
    }

    uint8_t decrypted_data[length];
    memcpy(decrypted_data, encrypted_data, length);

    // Decrypt the data
    AES_ECB_decrypt(&ctx, decrypted_data);

    // Process the decrypted data
    json_controller_parse((char*)decrypted_data);
}