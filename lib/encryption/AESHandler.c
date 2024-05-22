#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#include "aes.h"

static uint8_t key[16];

void AESHandler_init(uint8_t *input_key){
    for (int i = 0; i < 16; i++) {
        key[i] = input_key[i];
    }
}

void AESHandler_encrypt(uint8_t *data, uint8_t *encrypted_data, uint8_t *iv) {
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, data, AES_BLOCKLEN);
    memcpy(encrypted_data, data, AES_BLOCKLEN);
}

void AESHandler_decrypt(uint8_t *encrypted_data, uint8_t *decrypted_data, uint8_t *iv) {
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_decrypt_buffer(&ctx, encrypted_data, AES_BLOCKLEN);
    memcpy(decrypted_data, encrypted_data, AES_BLOCKLEN);
}

#define IV_SIZE 16
void generate_iv(unsigned char *iv) {
    srand(time(NULL));
    // Generate random bytes for the IV
    for (int i = 0; i < IV_SIZE; i++) {
        iv[i] = rand() % 256; // Generate a random byte (0-255)
    }
}
