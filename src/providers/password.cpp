#include "providers/password.hpp"

std::uint8_t MT19937Provider::generate_random_byte() {
    if (current_byte_index > 3 || current == 0) {
        current = generator();
        current_byte_index = 0;
    }

    // byte1 = (rand>>0) & 0xff;
    // byte2 = (rand>>8) & 0xff;
    // byte3 = (rand>>16) & 0xff;
    // byte4 = (rand>>24) &  0xff;

    std::uint8_t byte = (current >> (current_byte_index * 8)) & 0xff;
    current_byte_index++;
    return byte;
}

std::string MT19937Provider::generate_password(const int length, policy::PasswordPolicy policy) {
    std::string_view chosen_chars = policy::get_special_characters_for_policy(policy);
    const auto chosen_chars_length = chosen_chars.length();
    assertm(chosen_chars_length <= 255, "chosen_chars len should not be > 255");
    std::uniform_int_distribution<> distr(0, static_cast<int>(chosen_chars_length)); // define the range

    int pos = 0;
    auto bytes = std::vector<char>();
    for (int i = 0; i < length; i++) {
        pos = distr(this->generator);
        auto b = chosen_chars[pos];
        bytes.push_back(b);
    }

    return std::string(bytes.begin(), bytes.end());
}