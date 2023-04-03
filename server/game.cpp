#include "game.h"

Game::Game() {
    running = true;

    // Open server
    if (listener.listen(PORT) != sf::Socket::Done) {
        LOG("OPEN", "Error listening");
        exit(1);
    }
    listener.setBlocking(false);

    selector.add(listener);

    // Load question
    std::ifstream file(QUESTIONS_FILE);
    std::string line;
    while (std::getline(file, line)) {
        questions.push_back(Question(line));
    }
}

bool Game::isValidName(std::string name) {
    // check if name exist
    for (int i = 0; i < currentPlayer; i++) {
        if (players[i].name == name) return false;
    }
    return std::regex_match(name, std::regex(name_pattern));
}

bool Game::disconnectPlayer(sf::TcpSocket *client) {
    LOG("DISCONNECT", "Client disconnected: " << client->getRemoteAddress());
    for (int i = 0; i < players.size(); i++) {
        if (players[i].client == client) {
            players.erase(players.begin() + i);
            break;
        }
    }
    selector.remove(*client);
    delete client;
    return false;
}

bool Game::registerPlayer(sf::TcpSocket &client, sf::Packet &receive_packet) {
    // Read name
    std::string name;
    receive_packet >> name;
    if (!isValidName(name)) {
        LOG("REGISTER", "Invalid name");
        send_result(client, false, "Invalid name");
        return false;
    }

    // Add player
    players.push_back(Player(name, &client));

    LOG("REGISTER", "Register successfully");
    send_result(client, true, "Register successfully");
    return true;
}

void Game::gameStart() {
    LOG("START", "Game start");
    for (int i = 0; i < TOTAL_PLAYER; ++i) {
        sf::Packet p;
        p << (int)TOTAL_PLAYER << (int)(i + 1) << (int)questions.size();
        if (players[i].client->send(p) != sf::Socket::Done) {
            LOG("START", "Error sending packet");
            continue;
        }
    }
}

void Game::run() {
    while (running) {
        // Wait for one of the sockets to be ready for reading
        if (selector.wait()) {
            // Test the listener
            if (selector.isReady(listener)) {
                // The listener is ready: there is a pending connection
                sf::TcpSocket *client = new sf::TcpSocket;

                if (listener.accept(*client) != sf::Socket::Done) {
                    LOG("CONNECT", "Error accepting client");
                    delete client;
                    continue;
                }

                // Add the new client to the clients list
                clients.push_back(client);
                selector.add(*client);
                LOG("CONNECT", "New client connected: " << client->getRemoteAddress());
            } else {
                for (auto &client : clients) {
                    if (selector.isReady(*client)) {
                        sf::Packet receive_packet;
                        sf::Socket::Status status = client->receive(receive_packet);
                        if (status == sf::Socket::Disconnected) {
                            disconnectPlayer(client);
                            continue;
                        }

                        if (status != sf::Socket::Done) {
                            LOG("ERROR", "Error receiving packet");
                            continue;
                        }

                        // Read action
                        std::string action;
                        receive_packet >> action;
                        if (action == ACTION_REGISTER) {
                            if (players.size() >= TOTAL_PLAYER) {
                                LOG("REGISTER", "Game is full");
                                send_result(*client, false, "Game is full");
                                continue;
                            }

                            registerPlayer(*client, receive_packet);

                            if (players.size() == TOTAL_PLAYER) {
                                test();  // TEST TI NHE PRI, CO GI XOA DI
                                // gameStart(); // VOI LAI CO VE KHONG CAN CAI NAY DAU NHE PRI
                            }
                        } else if (action == ACTION_ANSWER) {
                        } else if (action == ACTION_SKIP) {
                        } else if (action == ACTION_EXIT) {
                        } else {
                            LOG("ERROR", "Invalid action");
                        }
                    }
                }
            }
        }
    }
}

void Game::test() {
    Question q;
    q.title = "Which one is the nhentai code for metamorphosis?";
    q.choice_A = "177013";
    q.choice_B = "177014";
    q.choice_C = "177015";
    q.choice_D = "177016";

    for (int i = 0; i < 10; i++) {
        sf::Packet send_packet;
        send_packet << q;
        if (players[i % 3].client->send(send_packet) != sf::Socket::Done) {
            LOG("START", "Error sending packet");
            continue;
        }

        sf::Packet receive_packet;

        while (!selector.isReady(*players[i % 3].client)) {
            selector.wait();
        }
        players[i % 3].client->receive(receive_packet);
        std::string answer;
        receive_packet >> answer >> answer;
        std::cout << "The client " << i % 3 << " answer with: " << answer << std::endl;
        if (answer == "A") {
            sf::Packet send_packet;
            send_packet << "CORRECT";
            players[i % 3].client->send(send_packet);
        } else {
            sf::Packet send_packet;
            send_packet << "WRONG";
            players[i % 3].client->send(send_packet);
        }
    }
    std::cout << "Done Test\n";
}