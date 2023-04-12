#include "../include/player.h"

Player::Player(sf::TcpSocket *client) {
    this->socket = client;
    skipped = false;
    registered = false;
}

Player::~Player() {
    delete socket;
}
