#include "application.h"
#include "connection_controller.h"
#include "dht11.h"
#include "display.h"
#include "pc_comm.h"
#include "wifi.h"
#include "connection_controller.h"
#include "json_controller.h"
#include "water_ec.h"
#include "ph_sensor.h"
#include "water_temperature.h"
#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

void serverCallback(char *buffer)
{
    pc_comm_send_string_blocking("Server >> ");
    pc_comm_send_string_blocking(buffer);
    pc_comm_send_string_blocking("\n");

    json_controller_parse(buffer);
}

void application_init() {
    pc_comm_init(9600, NULL);
    water_ec_init();
    ph_sensor_init();

    water_temperature_init();
    connection_controller_init(serverCallback);

    // ECC Key Generation
    uECC_set_rng(simple_rng);
    uECC_Curve curve = uECC_secp256r1();

    uECC_make_key(cloud_public_key, cloud_private_key, curve);
    pc_comm_send_string_blocking("Cloud public key:\n");
    print_hex(cloud_public_key, 64);
    pc_comm_send_string_blocking("Cloud private key:\n");
    print_hex(cloud_private_key, 32);

    uECC_make_key(target_public_key, target_private_key, curve);
    pc_comm_send_string_blocking("\nTarget public key:\n");
    print_hex(target_public_key, 64);
    pc_comm_send_string_blocking("Target private key:\n");
    print_hex(target_private_key, 32);

    // Compute shared secret
    uECC_shared_secret(cloud_public_key, target_private_key, secret_target, curve);
    pc_comm_send_string_blocking("Target Secret:\n");
    print_hex(secret_target, 32);

    uECC_shared_secret(target_public_key, cloud_private_key, secret_cloud, curve);
    pc_comm_send_string_blocking("Cloud Secret:\n");
    print_hex(secret_cloud, 32);

    // Derive AES key from shared secret
    derive_key(secret_target, aes_key);
}

void print_hex(uint8_t *buf, size_t len) {
    char buffer[4];
    for (size_t i = 0; i < len; i++) {
        sprintf(buffer, "%02X", buf[i]);
        pc_comm_send_string_blocking(buffer);
    }
    pc_comm_send_string_blocking("\n\n");
}

int simple_rng(uint8_t *dest, unsigned size) {
    static uint8_t value = 0;
    value++;
    for (unsigned i = 0; i < size; ++i) {
        dest[i] = value + i + 7;
    }
    return 1;
}

void derive_key(uint8_t *shared_secret, uint8_t *key) {
    sha256(shared_secret, 32, key);
};

void application_run() {
    pc_comm_send_string_blocking("Application running.\n");

    uint8_t data_to_encrypt[16] = "Hello, World!";
    uint8_t encrypted_data[16];
    uint8_t decrypted_data[16];

    // Encrypt data
    aes_encrypt_data(aes_key, data_to_encrypt, encrypted_data);
    pc_comm_send_string_blocking("Encrypted Data:\n");
    print_hex(encrypted_data, 16);

    // Decrypt data
    aes_decrypt_data(aes_key, encrypted_data, decrypted_data);
    pc_comm_send_string_blocking("Decrypted Data:\n");
    print_hex(decrypted_data, 16);
}

void aes_encrypt_data(uint8_t *key, uint8_t *data, uint8_t *encrypted_data) {
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);
    AES_ECB_encrypt(&ctx, data);
    memcpy(encrypted_data, data, 16);
}

void aes_decrypt_data(uint8_t *key, uint8_t *encrypted_data, uint8_t *data) {
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);
    AES_ECB_decrypt(&ctx, encrypted_data);
    memcpy(data, encrypted_data, 16);
};