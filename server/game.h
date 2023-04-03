#ifndef GAME_H
#define GAME_H

#include <SFML/Network.hpp>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

#include "constant.h"
#include "debug.h"
#include "player.h"
#include "question.h"

#define send_result(client, result, msg)            \
    {                                               \
        sf::Packet p;                               \
        p << result << msg;                         \
        if ((client).send(p) != sf::Socket::Done) { \
            LOG("ERROR", "Error sending packet");   \
        }                                           \
        LOG("MSG", msg);                            \
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
    bool disconnectPlayer(sf::TcpSocket *client);
    bool registerPlayer(sf::TcpSocket &client, sf::Packet &receive_packet);
    void gameStart();
    bool registerPlayer(sf::TcpSocket &client, Player &player);
    void test();

    void run();
};

#endif  // GAME_H