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

#ifndef VCPPWD_HPP
#define VCPPWD_HPP

#include <string>

namespace policy {
    constexpr std::string_view alphanumeric_w_extra_special_chars {
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%?&^`~*()-_=+[{]}\\|;:'\",<.>/"
    };
    constexpr auto alphanumeric_w_basic_special_chars = alphanumeric_w_extra_special_chars.substr(0, 70);
    constexpr auto alphanumeric = alphanumeric_w_extra_special_chars.substr(0, 62);

    enum class PasswordPolicy : int { 
        AlphaNumeric_AN00, // AN00
        AlphaNumericWithBasicSpecialChars_AN01, // AN01
        AlphaNumericWithSpecialChars_AN02 // AN02
    }; 

    std::string_view
    get_special_characters_for_policy(PasswordPolicy policy);
}

#endif // VCPPWD_HPP