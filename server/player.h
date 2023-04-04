#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Network.hpp>
#include <string>

struct Player {
    sf::TcpSocket *client;
    std::string name;
    bool alive;
    bool skipped;

    Player(std::string name, sf::TcpSocket *client);
};

#endif  // PLAYER_H