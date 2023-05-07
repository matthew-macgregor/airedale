#include <string>
#include <boost/crc.hpp>
#include "providers/checksum.hpp"

unsigned int
providers::checksum::generate_crc32_checksum(std::string input) {
    boost::crc_32_type crc;
    crc.process_bytes(input.data(), input.size());
    return crc.checksum();
}