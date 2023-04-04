#include "../include/player.h"

// Connect to server, if server is not open exit the program
Player::Player() {
    if (socket.connect(IP, PORT) != sf::Socket::Done) {
        LOG("CONNECT", "Error connecting to server");
        exit(0);
    }
    LOG("CONNECT", "Connected to server");
}

// Register a nickname for the player and send it to the server
// Return true if the nickname is valid and not taken
// Return false if the nickname is invalid or taken
// The name is valid if regex ^[a-zA-Z0-9_]{1,10}$ matches
// The name is taken if the server returns a boolean false
Response Player::register_account(std::string name) {
    sf::Packet send_packet;
    std::string action = ACTION_REGISTER;
    send_packet << action << name;

    if (socket.send(send_packet) != sf::Socket::Done) {
        LOG_ERROR("Error sending registration request");
        return Response{CODE_ERROR, "Error sending registration request"};
    }

    sf::Packet recv_packet;
    if (socket.receive(recv_packet) != sf::Socket::Done) {
        LOG_ERROR("Error receiving registration result");
        return Response{CODE_ERROR, "Error receiving registration result"};
    }

    int code;
    std::string msg;
    recv_packet >> code >> msg;
    LOG_INFO("Return code: " << code << ", message: " << msg);
    return Response{code, msg};
}

// Receive game info from server
void Player::receive_game_info() {
    sf::Packet recv_packet;
    if (socket.receive(recv_packet) != sf::Socket::Done) {
        LOG_ERROR("Error receiving game info");
        return;
    }

    recv_packet >> num_players >> player_id >> num_questions;
    LOG_INFO("Number of players: " << num_players);
    LOG_INFO("Player ID: " << player_id);
    LOG_INFO("Number of questions: " << num_questions);
}

// receive the question from server
Question Player::receive_question() {
    sf::Packet recv_packet;
    if (socket.receive(recv_packet) != sf::Socket::Done) {
        LOG_ERROR("Error receiving question");
        return Question();
    }

    Question question;
    recv_packet >> question;
    return question;
}

// Send the answer to server and receive answer result from server
// Could be "Correct" or "Wrong" or "Win"
Response Player::send_answer(std::string answer) {
    sf::Packet send_packet;
    std::string action = ACTION_ANSWER;
    send_packet << action << answer;
    if (socket.send(send_packet) != sf::Socket::Done) {
        LOG_ERROR("Error sending answer");
        return Response{CODE_ERROR, "Error sending answer"};
    }

    sf::Packet recv_packet;
    if (socket.receive(recv_packet) != sf::Socket::Done) {
        LOG_ERROR("Error receiving answer result");
        return Response{CODE_ERROR, "Error receiving answer result"};
    }

    int code;
    std::string msg;
    recv_packet >> code >> msg;
    LOG_INFO("Return code: " << code << ", message: " << msg);
    return Response{code, msg};
}

// skip the question
Response Player::skip_question() {
    if (!can_skip) return Response{CODE_ERROR, "You can only skip once"};

    sf::Packet send_packet;
    std::string action = ACTION_SKIP;
    send_packet << action;
    if (socket.send(send_packet) != sf::Socket::Done) {
        LOG_ERROR("Error sending skip request");
        return Response{CODE_ERROR, "Error sending skip request"};
    }

    can_skip = false;
    LOG_INFO("Skip success");
    return Response{CODE_SUCCESS, "Skip success"};
}