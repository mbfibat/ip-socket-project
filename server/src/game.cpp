#include "../include/game.h"

Game::Game() {
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
        std::string filename = entry.path().string();
        std::ifstream file(filename);
        Question question;
        while (file >> question) {
            if (question.title.size() > 0) {
                questions.push_back(question);
            }
        }
    }
    LOG_INFO("Loaded " << questions.size() << " questions");
}

void Game::init() {
    running = true;
    currentPlayer = 0;
    currentQuestion = 0;
    totalQuestion = 0;

    players.clear();
    selectedQuestion.clear();
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
                    if (client != NULL && selector.isReady(*client)) {
                        sf::Packet packet;
                        sf::Socket::Status status;

                        // Receive packet
                        status = client->receive(packet);
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

                        int action;
                        packet >> action;
                        // Handle action
                        switch (action) {
                            case ACTION_REGISTER:
                                handleRegister(*client, packet);
                                break;
                            case ACTION_ANSWER:
                                handleAnswer(*client, packet);
                                break;
                            case ACTION_SKIP:
                                handleSkip(*client, packet);
                                break;
                            default:
                                LOG_ERROR("Invalid action");
                                break;
                        }
                    }
                }
            }
        }
    }
}
