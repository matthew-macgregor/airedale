#define SODIUM_STATIC
#include <sodium.h>
#include <string>
#include <cstdio>
#include "crypto.hpp"

#ifndef RANDOM_BYTES_BUFFER_SZ
    #define RANDOM_BYTES_BUFFER_SZ 512
#endif

int mm_random_gen(const u_string passw) {
    if (sodium_init() < 0) {
        /* panic! the library couldn't be initialized; it is not safe to use */
        exit(1); // TODO: do something better
    }

    unsigned char key[crypto_generichash_KEYBYTES] = {0};
    std::memcpy(key, passw.data(), passw.length());

    unsigned char seed[crypto_generichash_BYTES]; // 32U
    crypto_generichash(seed, sizeof seed, passw.c_str(), passw.length(), key, crypto_generichash_KEYBYTES);

    puts("hash:");
    for (int i = 0; i < crypto_generichash_BYTES; i++) {
        printf("%x", seed[i]);
    }

    static const unsigned char nonce[crypto_stream_chacha20_ietf_NONCEBYTES] = { // 12U
        'A', 'i', 'r', 'e', 'd', 'a', 'l', 'e', 'S', 'o', 'd', 'i'  
    };

    unsigned char buf[RANDOM_BYTES_BUFFER_SZ];
    crypto_stream_chacha20_ietf((unsigned char *) buf, RANDOM_BYTES_BUFFER_SZ, nonce, seed);
    puts("\nrandombytes:");
    for (size_t i = 0; i < RANDOM_BYTES_BUFFER_SZ; i++) {
        printf("%x", buf[i]);
    }

    printf("\nYou have initialized libsodium. Lucky you.\n");

    return 0;
}