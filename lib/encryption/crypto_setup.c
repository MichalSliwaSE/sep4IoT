#include "crypto_setup.h"
#include "key_exchange.h"
#include "connection_controller.h"
#include "wifi.h"

// Initialize key exchange and generate keys
void initialize_key_exchange() {
    key_exchange_init();
    key_exchange_generate_keys();

    uint8_t public_key[65]; // 64 bytes for the key + 1 for null terminator
    key_exchange_get_public_key(public_key);

    // Transmit the public key to the server
    // connection_controller_transmit((char*)public_key, 64);
    wifi_command_TCP_transmit((char *)public_key, 64);
}