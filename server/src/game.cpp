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

    // Init variables
    for (auto &player : players) {
        player = NULL;
    }
}

void Game::init() {
    for (int i = 0; i < TOTAL_PLAYER; i++) {
        if (players[i] != NULL) {
            delete players[i];
            players[i] = NULL;
        }
    }

    selectedQuestion.clear();

    gameState = EnumGameState::WAITING_FOR_PLAYER;
    currentPlayer = 0;
    currentQuestion = 0;
    totalQuestion = 0;
}

void Game::run() {
    while (gameState != EnumGameState::GAME_FINISHED) {
        // Wait for one of the sockets to be ready for reading
        if (selector.wait(sf::milliseconds(DELAY_MS))) {
            // Test the listener
            if (selector.isReady(listener)) {
                handleNewConnection();
            } else {
                for (auto &player : players) {
                    if (player != NULL && selector.isReady(*player->socket)) {
                        LOG_INFO("Received packet from player " << player->name);
                        sf::Packet packet;
                        sf::Socket::Status status;

                        // Receive packet
                        status = player->socket->receive(packet);

                        // Disconnect
                        if (status == sf::Socket::Disconnected) {
                            handleDisconnect(player);
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
                                handleRegister(player, packet);
                                break;
                            case ACTION_ANSWER:
                                handleAnswer(player, packet);
                                break;
                            case ACTION_SKIP:
                                handleSkip(player, packet);
                                break;
                            default:
                                LOG_ERROR("Invalid action");
                                break;
                        }
                    }
                }
            }
        }

        // Check if all players are ready
        if (gameState == EnumGameState::WAITING_FOR_PLAYER) {
            if (isAllPlayerRegistered()) {
                gameStart();
                sendQuestion();
            }
        }
    }
}
