#include <cstdint>
#include <random>
#include <boost/random.hpp>

#include "policy.hpp"

#ifndef RANDOM_PROVIDER_HPP
#define RANDOM_PROVIDER_HPP
class RandomPasswordProvider
{
public:
    RandomPasswordProvider(){}
    virtual ~RandomPasswordProvider(){}
    virtual std::uint8_t generate_random_byte() = 0;
    virtual std::string generate_password(const int length, policy::PasswordPolicy policy) = 0;
};

class MT19937Provider : public RandomPasswordProvider {
public:
    MT19937Provider(std::uint32_t seed): 
        seed {seed}, current {0}, current_byte_index {0} {
        generator = std::mt19937{seed};
    }
    std::uint8_t generate_random_byte();
    std::string generate_password(const int length, policy::PasswordPolicy policy);
private:
    std::uint32_t seed {};
    std::mt19937 generator {};
    std::uint32_t current;
    std::uint8_t current_byte_index;
};

#endif