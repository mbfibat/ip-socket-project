#include "../include/player.h"

// Connect to server, if server is not open exit the program
Player::Player() {
    if (socket.connect(IP, PORT) != sf::Socket::Done) {
        LOG_ERROR("Error connecting to server");
        exit(0);
    }
    socket.setBlocking(false);
    selector.add(socket);
    LOG_INFO("Connected to server");

    can_skip = true;
}

void Player::handle_socket() {
    if (!selector.wait(sf::milliseconds(DELAY_MS))) {
        return;
    }

    if (selector.isReady(socket)) {
        int action;
        sf::Packet recv_packet;
        if (socket.receive(recv_packet) != sf::Socket::Done) {
            LOG_ERROR("Error receiving packet");
            return;
        }
        recv_packet >> action;

        if (action != wait_action) {
            LOG_ERROR("Error receiving packet, wrong action");
            return;
        }

        switch (action) {
            case ACTION_REGISTER: {
                int code;
                std::string msg;
                recv_packet >> code >> msg;
                LOG_INFO("Return code: " << code << ", message: " << msg);

                if (code != CODE_SUCCESS) {
                    screen.drawNamingScreen();
                    wait_action = ACTION_NONE;
                    // TODO: prompt error message
                } else {
                    wait_action = ACTION_GAME_INFO;
                }
                break;
            }
            case ACTION_GAME_INFO: {
                recv_packet >> num_players >> player_id >> num_questions;
                LOG_INFO("Number of players: " << num_players);
                LOG_INFO("Player ID: " << player_id);
                LOG_INFO("Number of questions: " << num_questions);

                wait_action = ACTION_QUESTION;
                break;
            }
            case ACTION_QUESTION: {
                Question question;
                recv_packet >> question;
                LOG_INFO("Question: " << question);

                this->question = question;
                wait_action = ACTION_NONE;
                screen.drawGameScreen(question);
                break;
            }
            case ACTION_ANSWER: {
                int code;
                std::string msg;
                recv_packet >> code >> msg;
                LOG_INFO("Return code: " << code << ", message: " << msg);

                if (code == CODE_CORRECT) {
                    wait_action = ACTION_QUESTION;
                    // TODO: animate correct answer
                } else if (code == CODE_WIN) {
                    wait_action = ACTION_NONE;
                    LOG_INFO("You win");
                    screen.drawWinScreen();
                } else if (code == CODE_LOSE) {
                    wait_action = ACTION_NONE;
                    LOG_INFO("You lose");
                    screen.drawGameOverScreen();
                } else if (code == CODE_ERROR) {
                    wait_action = ACTION_NONE;
                    LOG_ERROR(msg);
                    // TODO: prompt error message
                } else {
                    wait_action = ACTION_NONE;
                    LOG_ERROR("Error receiving answer result");
                }
                break;
            }
            case ACTION_SKIP: {
                int code;
                std::string msg;
                recv_packet >> code >> msg;
                LOG_INFO("Return code: " << code << ", message: " << msg);

                if (code == CODE_SUCCESS) {
                    LOG_INFO("Skip successful");
                    screen.drawWaitingForHostScreen();
                    wait_action = ACTION_QUESTION;
                } else {
                    LOG_INFO("You have already skipped");
                    wait_action = ACTION_NONE;
                }
            }
        }
    }
}
