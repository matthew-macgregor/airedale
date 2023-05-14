#include <cstdint>
#include <random>

#include "policy.hpp"

#ifndef RANDOM_PROVIDER_HPP
#define RANDOM_PROVIDER_HPP
class RandomPasswordProvider
{
public:
    RandomPasswordProvider(){}
    virtual ~RandomPasswordProvider(){}
    virtual std::string generate_password(const int length, policy::PasswordPolicy policy) = 0;
};



#endif