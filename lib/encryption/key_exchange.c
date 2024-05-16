#include "key_exchange.h"
#include "uECC.h"
#include <stdio.h>
#include <string.h>

static uint8_t private_key[32 + 1];
static uint8_t public_key[64 + 1];
static uECC_Curve curve;

static void simple_hash(uint8_t *output, const uint8_t *input);
static int custom_rng(uint8_t *dest, unsigned size);

void key_exchange_init() {
    curve = uECC_secp256r1();
}

void key_exchange_generate_keys() {
    uECC_set_rng(&custom_rng);
    uECC_make_key(public_key, private_key, curve);
}

void key_exchange_get_public_key(uint8_t *copy_public_key) {
    memcpy(copy_public_key, public_key, 64);
    copy_public_key[64] = '\0';
}

void key_exchange_generate_shared_secret(uint8_t *received_public_key, uint8_t *shared_secret) {
    uint8_t temp_secret[32];
    uECC_shared_secret(received_public_key, private_key, temp_secret, curve);
    simple_hash(shared_secret, temp_secret);
}

static void simple_hash(uint8_t *output, const uint8_t *input) {
    for (int i = 0; i < 16; i++) {
        output[i] = input[i];
    }
    output[16] = '\0';
}

static int custom_rng(uint8_t *dest, unsigned size) {
    static uint8_t seed = 0;
    seed++;
    for (unsigned i = 0; i < size; ++i) {
        dest[i] = seed + i + 7;
    }
    return 1;
}
