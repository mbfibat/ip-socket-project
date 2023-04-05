#include "../include/game.h"

bool Game::isValidName(std::string name) {
    // check if name exist
    for (int i = 0; i < players.size(); i++) {
        if (players[i].name == name) return false;
    }
    return std::regex_match(name, std::regex(name_pattern));
}

int Game::countAlivePlayer() {
    int count = 0;
    for (int i = 0; i < players.size(); i++) {
        if (players[i].alive) count++;
    }
    return count;
}

bool Game::disconnectPlayer(sf::TcpSocket *client) {
    // FIXME: handle disconnect correctly

    LOG_INFO("Client " << client->getRemoteAddress() << " disconnected");
    for (int i = 0; i < players.size(); i++) {
        if (players[i].client == client) {
            LOG_INFO("Player " << players[i].name << " disconnected");
            players[i].alive = false;
            break;
        }
    }
    selector.remove(*client);
    delete client;
    client = NULL;
    return false;
}

Response Game::registerPlayer(std::string name, sf::TcpSocket &client) {
    if (!isValidName(name)) {
        LOG_INFO("Invalid name: " << name);
        return Response{CODE_ERROR, "Invalid name"};
    }

    // Add player
    players.push_back(Player(name, &client));

    LOG_INFO("Player " << name << " registered");
    return Response{CODE_SUCCESS, "Registered"};
}

void Game::gameStart() {
    LOG_INFO("Game start");

    // Init game
    currentPlayer = 0;
    currentQuestion = 0;

    // Prepare question
    totalQuestion = players.size() * QUESTION_PER_PLAYER;
    selectedQuestion = pick(questions.size(), totalQuestion);
    for (int i = 0; i < totalQuestion; ++i) {
        questions[selectedQuestion[i]].id = i + 1;
    }

    // Send game info
    for (int i = 0; i < TOTAL_PLAYER; ++i) {
        send(*players[i].client, ACTION_GAME_INFO, (int)players.size() << i + 1 << totalQuestion);
    }
}

void Game::sendQuestion() {
    if (countAlivePlayer() == 0) {
        LOG_INFO("No player alive");
        running = false;
        return;
    }

    // Find alive player
    // FIXME: handle disconnect correctly
    while (!players[currentPlayer].alive) {
        currentPlayer = (currentPlayer + 1) % players.size();
    }

    // Send question
    send(*players[currentPlayer].client, ACTION_QUESTION, questions[selectedQuestion[currentQuestion]]);
    LOG_INFO("Send question " << currentQuestion << " to player " << players[currentPlayer].name);
}