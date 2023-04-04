#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

#define LOG(tag, x) std::cerr << tag << '\t' << x << '\n'
#define LOG_INFO(x) LOG("INFO", x)
#define LOG_ERROR(x) LOG("ERROR", x)

#endif  // DEBUG_H