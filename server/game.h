#ifndef GAME_H
#define GAME_H

#include <SFML/Network.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

#include "constant.h"
#include "debug.h"
#include "player.h"
#include "question.h"
#include "random.h"

#define send_result(client, result, msg)            \
    {                                               \
        sf::Packet p;                               \
        p << result << msg;                         \
        if ((client).send(p) != sf::Socket::Done) { \
            LOG_ERROR("Error sending result");      \
        }                                           \
    }

class Game {
    sf::TcpListener listener;
    std::vector<sf::TcpSocket *> clients;
    sf::SocketSelector selector;

    std::vector<Player> players;
    std::vector<Question> questions;
    std::vector<int> selectedQuestion;

    int totalQuestion;
    int currentPlayer;
    int currentQuestion;
    bool running;

public:
    Game();
    ~Game();

    // service
    bool isValidName(std::string name);
    bool registerPlayer(sf::TcpSocket &client, std::string name);
    bool disconnectPlayer(sf::TcpSocket *client);
    void gameStart();
    void sendQuestion();

    // handler
    void handleNewConnection();
    void handleRegister(sf::TcpSocket &client, sf::Packet &packet);
    void handleAnswer(sf::TcpSocket &client, sf::Packet &packet);
    void handleSkip(sf::TcpSocket &client, sf::Packet &packet);
    void handleExit(sf::TcpSocket &client, sf::Packet &packet);

    void run();
};

#endif  // GAME_H