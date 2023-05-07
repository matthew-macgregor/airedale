#include <string>

#ifndef PROVIDERS_CHECKSUM_HPP
#define PROVIDERS_CHECKSUM_HPP
namespace providers {
    namespace checksum {
        unsigned int generate_crc32_checksum(std::string input);
    }
}
#endif
