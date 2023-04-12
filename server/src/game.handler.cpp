#include "../include/game.h"

void Game::handleNewConnection() {
    LOG_INFO("Handle new connection");
    // Check if game is full or is playing
    if (countAlivePlayer() >= totalPlayer || gameState == EnumGameState::GAME_RUNNING) {
        LOG_INFO("Game is full or is playing");
        return;
    }

    // Accept new connection
    sf::TcpSocket *client = new sf::TcpSocket;
    if (listener.accept(*client) != sf::Socket::Done) {
        LOG_ERROR("Error accepting new connection");
        delete client;
        return;
    }
    LOG_INFO("New connection from " + client->getRemoteAddress().toString());
    client->setBlocking(false);
    selector.add(*client);

    // Find empty slot and add player
    for (int i = 0; i < totalPlayer; i++) {
        if (players[i] == NULL) {
            players[i] = new Player(client);
            break;
        }
    }
}

void Game::handleDisconnect(Player *&player) {
    LOG_INFO("Handle Disconnect");

    LOG_INFO("Client " << player->socket->getRemoteAddress() << " disconnected");
    selector.remove(*player->socket);
    delete player;
    player = NULL;
}

void Game::handleRegister(Player *&player, sf::Packet &packet) {
    LOG_INFO("Handle register");

    std::string name;
    packet >> name;
    auto [code, msg] = registerPlayer(name, player);
    send(*player->socket, ACTION_REGISTER, code << msg);
}

void Game::handleAnswer(Player *&player, sf::Packet &packet) {
    LOG_INFO("Handle answer");

    int questionId;
    std::string name, answer;
    packet >> name >> questionId >> answer;

    if (questionId != currentQuestion + 1) {
        LOG_INFO("Player " << name << " answered wrong question");
        send(*player->socket, ACTION_ANSWER, CODE_ERROR << "Wrong question");
        return;
    }

    if (player != players[currentPlayer]) {
        LOG_INFO("Player " << name << " answered wrong turn");
        send(*player->socket, ACTION_ANSWER, CODE_ERROR << "Wrong turn");
        return;
    }

    LOG_INFO("Player " << players[currentPlayer]->name << " answered " << answer);

    // If the player is the last one, he/she is a winner no matter what the result of his / her answer
    if (countAlivePlayer() == 1) {
        LOG_INFO("Player " << players[currentPlayer]->name << " is the last one, he/she is a winner");
        gameState = EnumGameState::GAME_FINISHED;
        send(*player->socket, ACTION_ANSWER, CODE_WIN << "You are the last one, you are a winner");
        handleDisconnect(player);
        return;
    }

    // If the player is not the last player, that player chooses to answer the
    // question and has a correct answer, the server will send the next question
    // to that player. If the question which is sent to the player is the last
    // question, that player is also the winner, no matter what the result of
    // his / her answer.
    if (answer == questions[selectedQuestion[currentQuestion]].answer) {
        LOG_INFO("Player " << players[currentPlayer]->name << " got correct answer");
        currentQuestion++;
        if (currentQuestion == totalQuestion - 1) {
            LOG_INFO("Player " << players[currentPlayer]->name << " meets the last question, he/she is a winner");
            gameState = EnumGameState::GAME_FINISHED;
            send(*player->socket, ACTION_ANSWER, CODE_WIN << "There's only one question left, you are a winner");
            handleDisconnect(player);
            return;
        }
        send(*player->socket, ACTION_ANSWER, CODE_CORRECT << "Correct answer");
        sendQuestion();
        return;
    }

    // If the player is not the last player, that player chooses to answer the
    // question and has a wrong answer, that player is disqualified.
    LOG_INFO("Player " << players[currentPlayer]->name << " got wrong answer");
    send(*player->socket, ACTION_ANSWER, CODE_LOSE << "Wrong answer");
    handleDisconnect(player);

    // Move to next player
    currentPlayer = (currentPlayer + 1) % totalPlayer;
    sendQuestion();
}

void Game::handleSkip(Player *&player, sf::Packet &packet) {
    LOG_INFO("Handle skip");

    int questionId;
    std::string name;
    packet >> name >> questionId;

    if (questionId != currentQuestion + 1) {
        LOG_INFO("Player " << name << " answered wrong question");
        send(*player->socket, ACTION_ANSWER, CODE_ERROR << "Wrong question");
        return;
    }

    if (player != players[currentPlayer]) {
        LOG_INFO("Player " << name << " answered wrong turn");
        send(*player->socket, ACTION_ANSWER, CODE_ERROR << "Wrong turn");
        return;
    }

    if (players[currentPlayer]->skipped) {
        LOG_INFO("Player " << players[currentPlayer]->name << " has already skipped");
        send(*player->socket, ACTION_SKIP, CODE_ERROR << "You have already skipped");
        return;
    }

    LOG_INFO("Player " << players[currentPlayer]->name << " skipped turn");
    send(*player->socket, ACTION_SKIP, CODE_SUCCESS << "Skipped");
    currentPlayer = (currentPlayer + 1) % totalPlayer;
    sendQuestion();
}
