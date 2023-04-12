#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "socket.h"

struct Player {
    sf::TcpSocket *socket;
    std::string name;
    bool registered;
    bool skipped;

    Player(sf::TcpSocket *client);
    ~Player();
};

#endif  // PLAYER_H
