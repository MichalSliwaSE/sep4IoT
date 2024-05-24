#pragma once
#include <stdint.h>
#include <sha1.h>

#define truncated_SHA1_hash_size 16

void hash_computeSHA1(const uint8_t *message, unsigned int length, uint8_t digest[truncated_SHA1_hash_size]);