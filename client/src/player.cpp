#include "../include/player.h"

// Connect to server, if server is not open exit the program
Player::Player() {
    if (socket.connect(IP, PORT) != sf::Socket::Done) {
        LOG("CONNECT", "Error connecting to server");
        exit(0);
    }
    socket.setBlocking(false);
    selector.add(socket);
    LOG_INFO("Connected to server");
}

void Player::handle_socket() {
    if (!selector.wait(sf::milliseconds(DELAY_MS))) {
        return;
    }

    if (selector.isReady(socket)) {
        if (wait_event == RCV_REGISTER_RESULT) {
            auto [code, msg] = receive_register_response();
            if (code != CODE_SUCCESS)
                screen.drawNamingScreen();
            else {
                wait_event = RCV_GAME_INFO;
            }
        } else if (wait_event == RCV_GAME_INFO) {
            receive_game_info();
            wait_event = RCV_QUESTION;
        } else if (wait_event == RCV_QUESTION) {
            Question question = receive_question();
            LOG_INFO("Question: " << question);
            screen.drawGameScreen(question);
        } else if (wait_event == RCV_ANSWER_RESULT) {
            auto [code, msg] = receive_answer_response();
            if (code == CODE_CORRECT) {
                wait_event = RCV_QUESTION;
            } else if (code == CODE_WRONG_TURN) {
                screen.drawWaitingForHostScreen();
                wait_event = RCV_QUESTION;
            } else if (code == CODE_ALREADY_SKIP) {
                // do nothing
            } else if (code == CODE_WIN) {
                screen.drawWinScreen();
            } else if (code == CODE_LOSE) {
                screen.drawGameOverScreen();
            } else {
                LOG_ERROR("Error receiving answer result");
            }
        } else if (wait_event == RCV_SKIP_RESULT) {
            auto [code, msg] = receive_answer_response();
            if (code == CODE_ALREADY_SKIP) {
                LOG_INFO("You have already skipped");
                // do nothing
            } else if (code == CODE_SUCCESS) {
                LOG_INFO("Skip successful");
                screen.drawWaitingForHostScreen();
                wait_event = RCV_QUESTION;
            } else {
                LOG_ERROR("Error receiving skip result");
            }
        }
    }
}
