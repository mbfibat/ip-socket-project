#include "../include/game.h"

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
        send_result(client, CODE_ERROR, "Game is full");
        return;
    }

    std::string name;
    packet >> name;
    if (!registerPlayer(client, name)) {
        return;
    }

    if (players.size() == TOTAL_PLAYER) {
        gameStart();
        sendQuestion();
    }
}

void Game::handleAnswer(sf::TcpSocket &client, sf::Packet &packet) {
    if (!checkCorrectTurn(client)) {
        LOG_INFO("Player " << players[currentPlayer].name << " is not your turn");
        send_result(client, CODE_WRONG_TURN, "It's not your turn");
        return;
    }

    std::string answer;
    packet >> answer;
    LOG_INFO("Player " << players[currentPlayer].name << " answered " << answer);

    // If the player is the last one, he/she is a winner no matter what the result of his / her answer
    if (countAlivePlayer() == 1) {
        LOG_INFO("Player " << players[currentPlayer].name << " is the last one, he/she is a winner");
        running = false;
        send_result(client, CODE_WIN, "You are the last one, you are a winner");
        return;
    }

    // If the player is not the last player, that player chooses to answer the
    // question and has a correct answer, the server will send the next question
    // to that player. If the question which is sent to the player is the last
    // question, that player is also the winner, no matter what the result of
    // his / her answer.
    if (answer[0] == questions[selectedQuestion[currentQuestion]].correct) {
        LOG_INFO("Player " << players[currentPlayer].name << " got correct answer");
        currentQuestion++;
        if (currentQuestion == totalQuestion - 1) {
            LOG_INFO("Player " << players[currentPlayer].name << " meets the last question, he/she is a winner");
            running = false;
            send_result(client, CODE_WIN, "There's only one question left, you are a winner");
            return;
        }
        send_result(client, CODE_CORRECT, "Correct answer");
        sendQuestion();
        return;
    }

    // If the player is not the last player, that player chooses to answer the
    // question and has a wrong answer, that player is disqualified.
    LOG_INFO("Player " << players[currentPlayer].name << " got wrong answer");
    players[currentPlayer].alive = false;
    send_result(client, CODE_LOSE, "Wrong answer");
    currentPlayer = (currentPlayer + 1) % players.size();
    sendQuestion();
}

void Game::handleSkip(sf::TcpSocket &client, sf::Packet &packet) {
    if (!checkCorrectTurn(client)) {
        LOG_INFO("Player " << players[currentPlayer].name << " is not your turn");
        send_result(client, CODE_WRONG_TURN, "It's not your turn");
        return;
    }

    if (players[currentPlayer].skipped) {
        LOG_INFO("Player " << players[currentPlayer].name << " has already skipped");
        send_result(client, CODE_ALREADY_SKIP, "You have already skipped");
        return;
    }

    LOG_INFO("Player " << players[currentPlayer].name << " skipped turn");
    send_result(client, CODE_SUCCESS, "Skipped");
    currentPlayer = (currentPlayer + 1) % players.size();
    sendQuestion();
}
