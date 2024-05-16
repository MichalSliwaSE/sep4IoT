#pragma once
#include "uECC.h"
#include "aes.h"
#include "sha256.h"

void application_init();
void application_run();

// Define key and secret buffers
extern uint8_t cloud_public_key[64];
extern uint8_t cloud_private_key[32];
extern uint8_t target_public_key[64];
extern uint8_t target_private_key[32];
extern uint8_t secret_target[32];
extern uint8_t secret_cloud[32];
extern uint8_t aes_key[32];