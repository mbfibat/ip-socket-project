#include "../include/player.h"

// Register a nickname for the player and send it to the server
// Return true if the nickname is valid and not taken
// Return false if the nickname is invalid or taken
// The name is valid if regex ^[a-zA-Z0-9_]{1,10}$ matches
// The name is taken if the server returns a boolean false
void Player::send_register_request(std::string name) {
    if (wait_action != ACTION_NONE) {
        LOG_ERROR("Cannot register, waiting for action: " << wait_action);
        return;
    }

    this->name = name;
    send(socket, ACTION_REGISTER, name);
    wait_action = ACTION_REGISTER;
}

// Send the answer to server and receive answer result from server
// Could be "Correct" or "Wrong" or "Win"
void Player::send_answer(std::string answer) {
    if (wait_action != ACTION_NONE) {
        LOG_ERROR("Cannot answer, waiting for action: " << wait_action);
        return;
    }

    send(socket, ACTION_ANSWER, name << question.id << answer);
    wait_action = ACTION_ANSWER;
}

// skip the question
void Player::send_skip_request() {
    if (wait_action != ACTION_NONE) {
        LOG_ERROR("Cannot skip, waiting for action: " << wait_action);
        return;
    }

    if (!can_skip) {
        LOG_INFO("Cannot skip");
        return;
    }

    send(socket, ACTION_SKIP, name << question.id);
    can_skip = false;
    wait_action = ACTION_SKIP;
}
