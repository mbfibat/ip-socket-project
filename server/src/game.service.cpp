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

bool Game::checkCorrectTurn(sf::TcpSocket &client) {
    return players[currentPlayer].client == &client;
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

bool Game::registerPlayer(sf::TcpSocket &client, std::string name) {
    if (!isValidName(name)) {
        LOG_INFO("Invalid name: " << name);
        send_result(client, CODE_ERROR, "Invalid name");
        return false;
    }

    // Add player
    players.push_back(Player(name, &client));

    LOG_INFO("Player " << name << " registered");
    send_result(client, CODE_SUCCESS, "Register successfully");
    return true;
}

void Game::gameStart() {
    LOG_INFO("Game start");

    // Send game info
    for (int i = 0; i < TOTAL_PLAYER; ++i) {
        sf::Packet p;
        p << (int)TOTAL_PLAYER << (int)(i + 1) << (int)questions.size();
        if (players[i].client->send(p) != sf::Socket::Done) {
            LOG_ERROR("Error sending game info to player " << players[i].name);
            continue;
        }
    }

    // Prepare question
    totalQuestion = players.size() * QUESTION_PER_PLAYER;
    selectedQuestion = pick(questions.size(), totalQuestion);

    // Init game
    currentPlayer = 0;
    currentQuestion = 0;
}

void Game::sendQuestion() {
    if (countAlivePlayer() == 0) {
        LOG_INFO("No player alive");
        running = false;
        return;
    }

    // Find alive player
    while (!players[currentPlayer].alive) {
        currentPlayer = (currentPlayer + 1) % players.size();
    }

    // Send question
    sf::Packet p;
    p << questions[selectedQuestion[currentQuestion]];
    if (players[currentPlayer].client->send(p) != sf::Socket::Done) {
        LOG_ERROR("Error sending question" << currentQuestion << " to player " << players[currentPlayer].name);
    }
    LOG_INFO("Send question " << currentQuestion << " to player " << players[currentPlayer].name);
}