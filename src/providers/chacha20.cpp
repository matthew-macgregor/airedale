#define SODIUM_STATIC
#include <sodium.h>
#include <string>
#include <cstring>
#include <cstdio>
#include <stdexcept>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <limits>
#include <algorithm>
#include <boost/random/uniform_smallint.hpp>

#include "providers/password.hpp"
#include "providers/chacha20.hpp"
#include "providers/sodium_init.hpp"
#include "util.hpp"
#include "policy.hpp"

inline static constexpr int RANDOM_BYTES_BUFFER_SZ=MAX_ALLOWED_PASSWORD_LENGTH;

static const unsigned char nonce[crypto_stream_chacha20_ietf_NONCEBYTES] = { // 12U
    'A', 'i', 'r', 'e', 'd', 'a', 'l', 'e', 'M', 'M', 'p', 'h'  
};

class CryptoStreamChaCha20Generator {
public:
    CryptoStreamChaCha20Generator(std::string initializer): initializer {initializer} {}

    using result_type = uint8_t;
    result_type extract() {
        SodiumInit::init();

        if (index == RANDOM_BYTES_BUFFER_SZ || index < 0) {
            // make sure that the initializer length will fit into seed buffer
            size_t initializer_length = std::min(initializer.length(), static_cast<size_t>(crypto_generichash_BYTES));
            std::memset(seed, 0, static_cast<size_t>(crypto_generichash_BYTES)); // clear the buffer
            std::memcpy(seed, initializer.data(), initializer_length); // set to the initializer
            crypto_stream_chacha20_ietf(static_cast<unsigned char *>(buffer), RANDOM_BYTES_BUFFER_SZ, nonce, seed);
            index = 0;
        }

        return buffer[index++];
    }

    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }
    result_type operator()() { return extract(); }

private:
    unsigned char buffer[RANDOM_BYTES_BUFFER_SZ] = {0};
    unsigned char seed[crypto_generichash_BYTES] = {0}; // 32U
    signed int index{-1};
    std::string initializer;
    static bool is_sodium_initialized;
};

void ChaCha20Provider::init() {}

std::string ChaCha20Provider::generate_password(const int length, policy::PasswordPolicy policy) {
    CryptoStreamChaCha20Generator generator{initializer};
    std::string_view chosen_chars = policy::get_special_characters_for_policy(policy);
    const auto chosen_chars_length = chosen_chars.length();
    assertm(chosen_chars_length <= 255, "chosen_chars len should not be > 255");
    // using boost to generate the uniform distribution because the std library implementation returns slightly
    // different results for msvc vs. g++. boost seems to be consistent, although this may not be guaranteed.
    boost::uniform_smallint<> distr(0, std::min(static_cast<int>(chosen_chars_length), (int)UINT8_MAX)); // define the range

    size_t pos = 0;
    auto bytes = std::vector<char>();
    for (int i = 0; i < length; i++) {
        pos = distr(generator);
        auto b = chosen_chars[pos];
        bytes.push_back(b);
    }

    return std::string(bytes.begin(), bytes.end());
}