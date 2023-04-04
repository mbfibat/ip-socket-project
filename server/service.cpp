#include "game.h"

bool Game::isValidName(std::string name) {
    // check if name exist
    for (int i = 0; i < players.size(); i++) {
        if (players[i].name == name) return false;
    }
    return std::regex_match(name, std::regex(name_pattern));
}

bool Game::disconnectPlayer(sf::TcpSocket *client) {
    LOG_INFO("Client " << client->getRemoteAddress() << " disconnected");
    for (int i = 0; i < players.size(); i++) {
        if (players[i].client == client) {
            LOG_INFO("Player " << players[i].name << " disconnected");
            players.erase(players.begin() + i);
            break;
        }
    }
    selector.remove(*client);
    delete client;
    return false;
}

bool Game::registerPlayer(sf::TcpSocket &client, std::string name) {
    if (!isValidName(name)) {
        LOG_INFO("Invalid name: " << name);
        send_result(client, false, "Invalid name");
        return false;
    }

    // Add player
    players.push_back(Player(name, &client));

    LOG_INFO("Player " << name << " registered");
    send_result(client, true, "Register successfully");
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
    // Send question
    sf::Packet p;
    p << questions[selectedQuestion[currentQuestion]];
    if (players[currentPlayer].client->send(p) != sf::Socket::Done) {
        LOG_ERROR("Error sending question" << currentQuestion << " to player " << players[currentPlayer].name);
    }
    LOG_INFO("Send question " << currentQuestion << " to player " << players[currentPlayer].name);
}