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

#include <cstdint>
#include <cassert>
#include "policy.hpp"
#include <random>

using namespace policy;

std::string_view
policy::get_special_characters_for_policy(PasswordPolicy policy) {
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