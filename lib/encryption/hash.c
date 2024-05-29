#include <sha1.h>
#include <stdio.h>
#include "hash.h"
#include <string.h>

void hash_computeSHA1(const uint8_t *message, unsigned int length, uint8_t digest[truncated_SHA1_hash_size])
{
    SHA1Context sha;
    int result;
    uint8_t full_digest[SHA1HashSize];

    // Reset the SHA1 context
    result = SHA1Reset(&sha);
    if (result != shaSuccess)
    {
        fprintf(stderr, "Error: SHA1Reset failed with error code %d\n", result);
        return;
    }

    // Input the message into the SHA1 context
    result = SHA1Input(&sha, message, length);
    if (result != shaSuccess)
    {
        fprintf(stderr, "Error: SHA1Input failed with error code %d\n", result);
        return;
    }

    // Get the full SHA-1 result from the SHA1 context
    result = SHA1Result(&sha, full_digest);
    if (result != shaSuccess)
    {
        fprintf(stderr, "Error: SHA1Result failed with error code %d\n", result);
        return;
    }

    // Copy the first 16 bytes of the full 20-byte digest to the truncated digest
    memcpy(digest, full_digest, truncated_SHA1_hash_size);
}