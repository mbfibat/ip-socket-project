#include "game.h"

void Game::handleNewConnection() {
    sf::TcpSocket *client = new sf::TcpSocket;
    if (listener.accept(*client) != sf::Socket::Done) {
        LOG_ERROR("Error accepting new connection");
        delete client;
        return;
    }
    LOG_INFO("New connection from " + client->getRemoteAddress().toString());
    client->setBlocking(false);
    selector.add(*client);
    clients.push_back(client);
}

void Game::handleRegister(sf::TcpSocket &client, sf::Packet &packet) {
    if (players.size() >= TOTAL_PLAYER) {
        LOG_INFO("Game is full");
        send_result(client, false, "Game is full");
        return;
    }

    std::string name;
    packet >> name;
    registerPlayer(client, name);

    if (players.size() == TOTAL_PLAYER) {
        gameStart();
        sendQuestion();
    }
}