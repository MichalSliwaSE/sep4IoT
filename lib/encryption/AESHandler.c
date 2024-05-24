#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "aes.h"

#define AES_BLOCKLEN 16 
#define IV_SIZE 16
static uint8_t key[16];


void AESHandler_init(uint8_t *input_key){
    for (int i = 0; i < 16; i++) {
        key[i] = input_key[i];
    }
}
void AESHandler_encrypt(char **message) {
    struct AES_ctx ctx;
    char iv[AES_BLOCKLEN];
    AESHandler_generate_iv(iv);

    // Get the length of the message
    size_t message_len = strlen(*message);

      // Reallocate memory for the message to accommodate the IV and encrypted message
    char *new_message = (char *)realloc(*message, AES_BLOCKLEN + message_len + 1);
    if (new_message == NULL) {
        // Memory allocation failed
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    *message = new_message;

     // Move the original message to make space for the IV at the beginning
    memmove(*message + AES_BLOCKLEN , *message, message_len + 1);

    // Copy the IV to the beginning of the message buffer
    memcpy(*message, iv, AES_BLOCKLEN);

    // Initialize the AES context with the key and IV
    AES_init_ctx_iv(&ctx, (uint8_t*)key, (uint8_t*)iv);

    // Encrypt the data using AES in CBC mode
    AES_CBC_encrypt_buffer(&ctx, (uint8_t*)(*message + AES_BLOCKLEN ), message_len);

}

void AESHandler_decrypt(char *message) {

     struct AES_ctx ctx;

    char iv[AES_BLOCKLEN];
    memcpy(iv, message, AES_BLOCKLEN);

    // Get the length of the encrypted message
    size_t encrypted_data_len = strlen(message) - AES_BLOCKLEN;

    // Initialize the AES context with the key and IV
    AES_init_ctx_iv(&ctx, (uint8_t*)key, (uint8_t*)iv);

    // Decrypt the data using AES in CBC mode
    AES_CBC_decrypt_buffer(&ctx, (uint8_t*)(message + AES_BLOCKLEN), encrypted_data_len);

    // Move the decrypted message to the beginning of the buffer
    memmove(message, message + AES_BLOCKLEN, encrypted_data_len + 1);
}


void AESHandler_generate_iv(unsigned char *iv) {
    // Generate random bytes for the IV
    for (int i = 0; i < AES_BLOCKLEN; i++) {
        iv[i] = rand() % 256; // Generate a random byte (0-255)
    }
}