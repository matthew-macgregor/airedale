#include "password.hpp"

#ifndef PROVIDERS_CHACHA20_HPP
#define PROVIDERS_CHACHA20_HPP

class ChaCha20Provider : public RandomPasswordProvider {
public:
    ChaCha20Provider(std::string initializer): initializer {initializer} {}
    std::string generate_password(const int length, policy::PasswordPolicy policy);
private:
    std::string initializer{};
    void init();
};

#endif