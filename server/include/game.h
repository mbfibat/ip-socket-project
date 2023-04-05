#ifndef GAME_H
#define GAME_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

#include "constant.h"
#include "logger.h"
#include "player.h"
#include "question.h"
#include "random.h"
#include "socket.h"

typedef struct {
    int code;
    std::string msg;
} Response;

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
    void init();
    void run();

    bool isValidName(std::string name);
    int countAlivePlayer();
    Response registerPlayer(std::string name, sf::TcpSocket &client);
    bool disconnectPlayer(sf::TcpSocket *client);
    void gameStart();
    void sendQuestion();

    void handleNewConnection();
    void handleRegister(sf::TcpSocket &client, sf::Packet &packet);
    void handleAnswer(sf::TcpSocket &client, sf::Packet &packet);
    void handleSkip(sf::TcpSocket &client, sf::Packet &packet);
};

#endif  // GAME_H