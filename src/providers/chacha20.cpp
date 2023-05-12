#define SODIUM_STATIC
#include <sodium.h>
#include <string>
#include <cstdio>
#include <stdexcept>
#include "providers/password.hpp"
#include "providers/chacha20.hpp"
#include "util.hpp"

inline static constexpr int RANDOM_BYTES_BUFFER_SZ=MAX_ALLOWED_PASSWORD_LENGTH;

void ChaCha20Provider::init() {
    int result = sodium_init();
    if (result < 0) {
        /* panic! the library couldn't be initialized; it is not safe to use */
        throw std::runtime_error("libsodium failed to initialize with error: " + std::to_string(result)); // C++11
    }
}

std::string ChaCha20Provider::generate_password(const int length, policy::PasswordPolicy policy) {
    static const unsigned char nonce[crypto_stream_chacha20_ietf_NONCEBYTES] = { // 12U
        'A', 'i', 'r', 'e', 'd', 'a', 'l', 'e', 'M', 'M', 'p', 'h'  
    };
    init();

    unsigned char buf[RANDOM_BYTES_BUFFER_SZ];
    unsigned char seed[crypto_generichash_BYTES] = {0}; // 32U
    std::memcpy(seed, initializer.data() + length, crypto_generichash_BYTES);
    crypto_stream_chacha20_ietf((unsigned char *) buf, RANDOM_BYTES_BUFFER_SZ, nonce, seed);

    return hex_str(buf, RANDOM_BYTES_BUFFER_SZ).substr(0, length);
}