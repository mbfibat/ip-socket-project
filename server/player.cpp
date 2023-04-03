#include "player.h"

Player::Player(std::string name, sf::TcpSocket *client) {
    this->name = name;
    this->client = client;
}
