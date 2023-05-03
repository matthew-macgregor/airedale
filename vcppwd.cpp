/*
   Copyright (c) Matthew MacGregor, 2023

    This file is part of Airedale.

    Airedale is free software: you can redistribute it and/or modify it 
    under the terms of the GNU General Public License as published by the Free 
    Software Foundation, either version 3 of the License, or (at your option) 
    any later version.

    Airedale is distributed in the hope that it will be useful, but WITHOUT ANY 
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU General Public License for more 
    details.

    You should have received a copy of the GNU General Public License along 
    with Airedale. If not, see <https://www.gnu.org/licenses/>. 
*/

#include "vcppwd.hpp"
#include <cstdint>
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))

using namespace vcppwd;

uint8_t
rand_range(boost::random::mt19937 &gen, std::uint8_t max) {
    unsigned char rem = 0;
    unsigned char buck = 0;
    unsigned char bytes[4];

    while (true) {
        std::uint32_t rand = gen();
        for (std::uint8_t i = 0; i < 4; i++) {
            // byte1 = (rand>>0) & 0xff;
            // byte2 = (rand>>8) & 0xff;
            // byte3 = (rand>>16) & 0xff;
            // byte4 = (rand>>24) &  0xff;

            bytes[i] = (rand >> i * 8) & 0xff;
            if (255 == bytes[i]) {
                continue;
            }

            rem = 255 % max;
            buck = 255 / max;

            if (bytes[i] < (255 - rem)) {
                return static_cast<uint8_t>(bytes[i] / buck);
            }
        }
    }
}

std::string_view
get_special_characters_for_policy(PasswordPolicy policy) {
    switch (policy) {
        case PasswordPolicy::AlphaNumeric_AN00:
            return alphanumeric;
        case PasswordPolicy::AlphaNumericWithBasicSpecialChars_AN01:
            return alphanumeric_w_basic_special_chars;
        case PasswordPolicy::AlphaNumericWithSpecialChars_AN02:
        default:
            return alphanumeric_w_extra_special_chars;
    }
}

std::string
vcppwd::generate_password(const int length, std::uint32_t seed, PasswordPolicy policy) {
    seed = seed ^ length;
    boost::random::mt19937 gen{seed}; // TODO: generic; replace
    std::string_view chosen_chars = get_special_characters_for_policy(policy);
    const auto len = chosen_chars.length();
    assertm(len <= 255, "chosen_chars len should not be > 255");

    int pos = 0;
    auto bytes = std::vector<char>(length);
    for (int i = 0; i < length; i++) {
        pos = rand_range(gen, static_cast<std::uint8_t>(chosen_chars.length()));
        bytes.push_back(chosen_chars[pos]);
    }

    return std::string(bytes.begin(), bytes.end());
}

unsigned int
vcppwd::generate_checksum(std::string password, std::string realm) {
    boost::crc_32_type crc;
    crc.process_bytes(password.data(), password.size());
    crc.process_bytes(realm.data(), realm.size());
    return crc.checksum();
}