#include "password.hpp"
#include "checksum.hpp"

#ifndef PROVIDERS_MY19937_HPP
#define PROVIDERS_MY19937_HPP
class MT19937Provider : public RandomPasswordProvider {
public:
    MT19937Provider(std::uint32_t seed): seed {seed} {
        generator = std::mt19937{seed};
    }
    MT19937Provider(std::string initializer, std::uint32_t variant): current {0}, current_byte_index {0} {
        seed = providers::checksum::generate_crc32(initializer);
        generator = std::mt19937{seed ^ variant};
    }
    std::string generate_password(const int length, policy::PasswordPolicy policy);

private:
    std::uint32_t seed {0};
    std::mt19937 generator {};
    std::uint32_t current {0};
    std::uint8_t current_byte_index {0};
};
#endif