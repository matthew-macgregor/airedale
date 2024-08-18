#include <string>
#include <cstring>
#include <boost/crc.hpp>
#include <sodium.h>
#include "providers/checksum.hpp"
#include "util.hpp"

unsigned int
providers::checksum::generate_crc32(std::string input) {
    boost::crc_32_type crc;
    crc.process_bytes(input.data(), input.size());
    return crc.checksum();
}

std::string
providers::checksum::generate_BLAKE2b(std::string input) {
    unsigned char message[BLAKE2B_MESSAGE_MAX_SZ] = {0}; // 32U
    std::memcpy(message, input.data(), BLAKE2B_MESSAGE_MAX_SZ);
    assertm(input.length() <= BLAKE2B_MESSAGE_MAX_SZ, "Input length out of bounds");

    unsigned char hash[crypto_generichash_BYTES] = {0}; // 32U
    crypto_generichash(hash, crypto_generichash_BYTES, message, BLAKE2B_MESSAGE_MAX_SZ, NULL, 0);
    return hex_str(hash, crypto_generichash_BYTES);
}
