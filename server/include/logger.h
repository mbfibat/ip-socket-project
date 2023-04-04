#ifndef LOGGER_H
#define LOGGER_H

#define LOG(tag, x) std::cerr << tag << '\t' << x << '\n'
#define LOG_INFO(x) LOG("INFO", x)
#define LOG_ERROR(x) LOG("ERROR", x)

#endif  // LOGGER_H