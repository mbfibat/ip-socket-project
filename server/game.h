#ifndef GAME_H
#define GAME_H

#include <SFML/Network.hpp>
#include <iostream>
#include <regex>

#include "player.h"
#include "utility.h"

class Game {
    sf::TcpListener listener;
    sf::TcpSocket client[TOTAL_PLAYER];
    int currentPlayer = 0;
    Player player[TOTAL_PLAYER];

public:
    bool isValidName(std::string name);
    bool registerPlayer(sf::TcpSocket &client, Player &player);

    void run();
};

#endif  // GAME_H