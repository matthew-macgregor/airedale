#include <string>
#include "util.hpp"

#ifndef PROVIDERS_CHECKSUM_HPP
#define PROVIDERS_CHECKSUM_HPP

namespace providers {
    namespace checksum {
        typedef std::basic_string<unsigned char> u_string;
        constexpr int BLAKE2B_MESSAGE_MAX_SZ = MAX_ALLOWED_PASSWORD_LENGTH;
        unsigned int generate_crc32(std::string input);
        std::string generate_BLAKE2b(std::string input);
    }
}
#endif
