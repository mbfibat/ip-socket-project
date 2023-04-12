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
    sf::SocketSelector selector;

    std::vector<Player *> players;
    std::vector<Question> questions;
    std::vector<int> selectedQuestion;

    int totalPlayer;
    int currentPlayer;

    int totalQuestion;
    int currentQuestion;

    EnumGameState gameState;

public:
    Game();
    void init();
    void run();

    bool isValidName(std::string name);
    bool isAllPlayerRegistered();
    int countAlivePlayer();
    Response registerPlayer(std::string name, Player *&player);
    void gameStart();
    void sendQuestion();

    void handleDisconnect(Player *&player);
    void handleNewConnection();
    void handleRegister(Player *&player, sf::Packet &packet);
    void handleAnswer(Player *&player, sf::Packet &packet);
    void handleSkip(Player *&player, sf::Packet &packet);
};

#endif  // GAME_H
