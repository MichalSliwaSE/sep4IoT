#ifndef AESHANDLER_H
#define AESHANDLER_H

#include <stdint.h>

void AESHandler_init(uint8_t *input_key);
void AESHandler_encrypt(uint8_t *data, uint8_t *encrypted_data, uint8_t *iv);
void AESHandler_decrypt(uint8_t *encrypted_data, uint8_t *decrypted_data, uint8_t *iv);
void generate_iv(unsigned char *iv);

#endif 
