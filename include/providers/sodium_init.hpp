#define SODIUM_STATIC
#include <sodium.h>

#ifndef PROVIDERS_SODIUM_INIT_HPP
#define PROVIDERS_SODIUM_INIT_HPP

class SodiumInit {
public:
    static void init() {
        if (is_sodium_initialized) { return; }
        int result = sodium_init();
        if (result < 0) {
            /* panic! the library couldn't be initialized; it is not safe to use */
            throw std::runtime_error("libsodium failed to initialize with error: " + std::to_string(result)); // C++11
        }
        is_sodium_initialized = true;
    }

private:
    static bool is_sodium_initialized;
};

bool SodiumInit::is_sodium_initialized = false;

#endif // include guard