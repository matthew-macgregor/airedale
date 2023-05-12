#include <iostream>
#include <iomanip>
#include <sstream>
// #include "util.hpp"

std::string hex_str(const uint8_t *data, int len){
     std::stringstream ss;
     ss << std::hex;

     for( int i(0) ; i < len; ++i ) {
         ss << std::setw(2) << std::setfill('0') << (int)data[i];
     }

     return ss.str();
}
