#include <cassert>
#include "providers/password.hpp"
#include "providers/checksum.hpp"
#include "providers/mt19937.hpp"

std::string MT19937Provider::generate_password(const int length, policy::PasswordPolicy policy) {
    std::string_view chosen_chars = policy::get_special_characters_for_policy(policy);
    const auto chosen_chars_length = chosen_chars.length();
    assertm(chosen_chars_length <= 255, "chosen_chars len should not be > 255");
    std::uniform_int_distribution<> distr(0, static_cast<int>(chosen_chars_length - 1)); // define the range

    int pos = 0;
    auto bytes = std::vector<char>();
    for (int i = 0; i < length; i++) {
        pos = distr(this->generator);
        auto b = chosen_chars[pos];
        bytes.push_back(b);
    }

    return std::string(bytes.begin(), bytes.end());
}