#include "key_exchange.h"
#include "uECC.h"
#include <stdio.h>
#include <string.h>
#include "AESHandler.h"
#include "hash.h"

bool key_exchange_completed = false;

static uint8_t private_key[32 + 1];
static uint8_t public_key[64 + 1];
static uECC_Curve curve;

#define TRUNCATED_HASH_SIZE 16
#define IV_SIZE 16

static int custom_rng(uint8_t *dest, unsigned size);

void key_exchange_init() {
    curve = uECC_secp256r1();
}

void key_exchange_generate_keys() {
    uECC_set_rng(&custom_rng);
    uECC_make_key(public_key, private_key, curve);
}

void key_exchange_get_public_key(uint8_t *copy_public_key) {
     for (int i = 0; i < 64; i++)
    {
        copy_public_key[i] = public_key[i];
    }
    copy_public_key[64] = '\0';
}

void key_exchange_generate_shared_secret(uint8_t *received_public_key, uint8_t *shared_secret) {
    uint8_t temp_secret[32];
    uECC_shared_secret(received_public_key, private_key, temp_secret, curve);
    // Hash the generated secret and truncate it
    uint8_t truncated_hash[TRUNCATED_HASH_SIZE];
    hash_computeSHA1(truncated_hash, TRUNCATED_HASH_SIZE, temp_secret);

    // Copy the truncated hash to the secret
    for (int i = 0; i < TRUNCATED_HASH_SIZE; i++)
    {
        shared_secret[i] = truncated_hash[i];
    }
}

static int custom_rng(uint8_t *dest, unsigned size) {
    static uint8_t seed = 0;
    seed++;
    for (unsigned i = 0; i < size; ++i) {
        dest[i] = seed + i + 7;
    }
    return 1;
}
