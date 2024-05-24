#ifndef AESHANDLER_H
#define AESHANDLER_H

#include <stdint.h>

void AESHandler_init(uint8_t *input_key);
void AESHandler_encrypt(char **message);
void AESHandler_decrypt(char *message);
void AESHandler_generate_iv(unsigned char *iv);

#endif 
