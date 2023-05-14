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


#include <iostream>
#include <ctime>
#include <cstdint>
#include <string>
#include <iterator>
#include <exception>
#include <cstring>
#include <cstdio> // getchar
#include <boost/algorithm/string.hpp>

#include "clipp.h"
#include "policy.hpp"
#include "providers/include.hpp"

#define GETPASS_IMPL
#include "getpass.h"

using namespace clipp;
using namespace policy;
using namespace boost::algorithm;

// c++ -std=c++20 -Iboost_1_81_0 -Wno-deprecated-declarations main.cpp -o main
int main(int argc, char** argv)
{
    bool quiet = false, use_mt19937 = false;
    uint32_t password_length = 42;
    std::string passphrase = "", realm = "", policy = "AN02";

    auto cli = (
        required("-r", "--realm") & value("realm identifier", realm),
        option("-i", "--insecure").set(use_mt19937).doc("allow insecure PRNG (mt19937)"),
        option("-p", "--passphrase", "--password") & value("primary passphrase", passphrase),
        option("-q", "--quiet").set(quiet).doc("quiet/script mode"),
        option("--policy") & value("password policy (AN00|AN01|AN02)", policy),
        option("-l", "--length") & value("generated password length", password_length)
    );

    if (!parse(argc, argv, cli)) {
        std::cout << "Airedale Deterministic Password Generator\n";
        std::cout << "Version v0.0.1\n";
        std::cout << make_man_page(cli, "airedale");
        exit(EXIT_FAILURE);
    }

    if (passphrase.empty()) {
        if (!quiet) std::cerr << "Enter passphrase: ";
        constexpr int password_max_len = 1024;
        char password_cstr[password_max_len] = {0};
        if (gpwd_get_password(password_cstr, password_max_len) > 0) {
            passphrase = std::string{password_cstr};
            if (!quiet) std::cerr << '\n';
        }
    }

    if (passphrase.empty()) {
        std::cout << "Password is required" << std::endl; // TODO: prompt
        exit(1);
    }

    trim(passphrase);

    PasswordPolicy password_policy = PasswordPolicy::AlphaNumericWithSpecialChars_AN02;
    if (false == policy.empty()) {
        if (policy == "AN00") {
            password_policy = PasswordPolicy::AlphaNumeric_AN00;
        } else if (policy == "AN01") {
            password_policy = PasswordPolicy::AlphaNumericWithBasicSpecialChars_AN01;
        } else if (policy == "AN02") {
            password_policy = PasswordPolicy::AlphaNumericWithSpecialChars_AN02;
        }
    }

    auto prng_name = use_mt19937 ? "mt19937" : "chacha20";
    auto checksum = providers::checksum::generate_crc32(passphrase + realm + policy + std::to_string(password_length) + prng_name);
    if (!quiet) std::cout << "Checksum: " << std::hex << checksum << std::dec << '\n';

    if (use_mt19937) {
        auto prov = MT19937Provider{passphrase + realm, password_length};
        auto passwd = prov.generate_password(password_length, password_policy);
        if (!quiet) std::cout << "Password: ";
        std::cout << passwd;
        if (!quiet) std::cout << std::endl;
    } else {
        auto prov = ChaCha20Provider{passphrase + realm};
        auto passwd = prov.generate_password(password_length, password_policy);
        if (!quiet) std::cout << "Password: ";
        std::cout << passwd;
        if (!quiet) std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}
