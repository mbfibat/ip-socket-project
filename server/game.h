#ifndef GAME_H
#define GAME_H

#include <SFML/Network.hpp>
#include <iostream>
#include <regex>
#include <vector>

#include "constant.h"
#include "debug.h"
#include "player.h"
#include "question.h"

#define send_result(client, result, msg) \
    {                                    \
        sf::Packet p;                    \
        p << result << msg;              \
        (client).send(p);                \
    }

class Game {
    sf::TcpListener listener;
    std::vector<sf::TcpSocket *> clients;
    sf::SocketSelector selector;

    std::vector<Player> players;
    std::vector<Question> questions;

    int currentPlayer = 0;
    bool running;

public:
    Game();

    bool isValidName(std::string name);
    bool registerPlayer(sf::TcpSocket &client, sf::Packet &receive_packet);

    void run();
};

#endif  // GAME_H