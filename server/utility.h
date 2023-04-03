#ifndef CONSTANT_H
#define CONSTANT_H

#include <string>

#define name_pattern "[a-zA-Z0-9_]{1,10}"

const std::string IP = "127.0.0.1";
const int PORT = 5000;
const int TOTAL_PLAYER = 3;

#define perr(result, msg)                 \
    {                                     \
        if (result != sf::Socket::Done) { \
            std::cout << msg << '\n';     \
            exit(1);                      \
        }                                 \
    }

#define send_result(client, result) \
    {                               \
        sf::Packet p;               \
        p << result;                \
        client.send(p);             \
    }

#endif  // CONSTANT_H