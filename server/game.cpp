#include "game.h"

Game::Game() {
    running = true;

    // Open listener
    if (listener.listen(PORT) != sf::Socket::Done) {
        LOG_ERROR("Error opening listener");
        exit(1);
    }
    listener.setBlocking(false);
    selector.add(listener);

    // Load question
    std::string path = DATA_FOLDER;
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        std::string file_name = entry.path().string();
        std::ifstream file(file_name);
        std::string line;
        while (std::getline(file, line)) {
            questions.push_back(Question(line));
        }
    }
}

Game::~Game() {
    for (auto &client : clients) {
        delete client;
    }
}

void Game::run() {
    while (running) {
        // Wait for one of the sockets to be ready for reading
        if (selector.wait()) {
            // Test the listener
            if (selector.isReady(listener)) {
                handleNewConnection();
            } else {
                for (auto &client : clients) {
                    if (selector.isReady(*client)) {
                        // Receive packet
                        sf::Packet receive_packet;
                        sf::Socket::Status status = client->receive(receive_packet);

                        // Disconnect
                        if (status == sf::Socket::Disconnected) {
                            disconnectPlayer(client);
                            continue;
                        }

                        // Error
                        if (status != sf::Socket::Done) {
                            LOG_ERROR("Error receiving packet");
                            continue;
                        }

                        // Read action
                        std::string action;
                        receive_packet >> action;
                        if (action == ACTION_REGISTER) {
                            handleRegister(*client, receive_packet);
                        } else if (action == ACTION_ANSWER) {
                        } else if (action == ACTION_SKIP) {
                        } else if (action == ACTION_EXIT) {
                        } else {
                            LOG_ERROR("Invalid action");
                        }
                    }
                }
            }
        }
    }
}
