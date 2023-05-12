#include <string>

#ifndef UTIL_HPP
#define UTIL_HPP

#define assertm(exp, msg) assert(((void)msg, exp))
constexpr int MAX_ALLOWED_PASSWORD_LENGTH = 2048;
std::string hex_str(const uint8_t *data, int len);

#endif