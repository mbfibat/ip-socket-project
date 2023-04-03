#include "game.h"

Game::Game() {
    running = true;

    // Open server
    if (listener.listen(PORT) != sf::Socket::Done) {
        LOG("Error listening");
        exit(1);
    }
    listener.setBlocking(false);

    selector.add(listener);

    // Load question
}

bool Game::isValidName(std::string name) {
    // check if name exist
    for (int i = 0; i < currentPlayer; i++) {
        if (players[i].name == name) return false;
    }
    return std::regex_match(name, std::regex(name_pattern));
}

bool Game::registerPlayer(sf::TcpSocket &client, sf::Packet &receive_packet) {
    // Read name
    std::string name;
    receive_packet >> name;
    if (!isValidName(name)) {
        LOG("Invalid name");
        send_result(client, false, "Invalid name");
        return false;
    }

    // Add player
    players.push_back(Player(name));

    LOG("Register successfully");
    send_result(client, true, "Register successfully");
    return true;
}

void Game::run() {
    while (running) {
        if (selector.wait()) {
            // Test the listener
            if (selector.isReady(listener)) {
                // The listener is ready: there is a pending connection
                sf::TcpSocket *client = new sf::TcpSocket;

                if (listener.accept(*client) != sf::Socket::Done) {
                    LOG("Error accepting client");
                    delete client;
                    continue;
                }

                // Add the new client to the clients list
                clients.push_back(client);
                selector.add(*client);
                LOG("New client connected: " << client->getRemoteAddress());
            } else {
                for (auto &client : clients) {
                    if (selector.isReady(*client)) {
                        sf::Packet receive_packet;
                        if (client->receive(receive_packet) != sf::Socket::Done) {
                            LOG("Error receiving packet");
                            continue;
                        }

                        // Read action
                        std::string action;
                        receive_packet >> action;
                        if (action == ACTION_REGISTER) {
                            if (players.size() >= TOTAL_PLAYER) {
                                LOG("Game is full");
                                send_result(*client, false, "Game is full");
                                continue;
                            }
                            registerPlayer(*client, receive_packet);
                        } else if (action == ACTION_ANSWER) {
                        } else if (action == ACTION_EXIT) {
                        } else {
                            LOG("Invalid action");
                        }
                    }
                }
            }
        }
    }
}