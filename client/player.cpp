#include "player.h"

Player::Player() {}

// Connect to server, if server is not open return false
bool Player::connect() {
    if (socket.connect(IP, PORT) != sf::Socket::Done) {
        LOG("CONNECT", "Error connecting to server");
        return false;
    }
    LOG("CONNECT", "Connected to server");
    return true;
}

// Register a nickname for the player and send it to the server
// Return true if the nickname is valid and not taken
// Return false if the nickname is invalid or taken
// The name is valid if regex ^[a-zA-Z0-9_]{1,10}$ matches
// The name is taken if the server returns a boolean false
bool Player::register_account(std::string name) {
    sf::Packet send_packet;
    std::string action = ACTION_REGISTER;
    send_packet << action << name;

    if (socket.send(send_packet) != sf::Socket::Done) {
        LOG("REGISTER", "Error sending packet");
        return false;
    }

    sf::Packet recv_packet;
    if (socket.receive(recv_packet) != sf::Socket::Done) {
        LOG("REGISTER", "Error receiving packet");
        return false;
    }

    bool is_valid;
    std::string msg;
    recv_packet >> is_valid >> msg;
    LOG("REGISTER", msg);
    return is_valid;
}

// Receive game info from server
void Player::receive_game_info() {
    sf::Packet recv_packet;
    if (socket.receive(recv_packet) != sf::Socket::Done) {
        LOG("GAME_INFO", "Error receiving packet");
        return;
    }

    int total_player, player_id, total_question;
    recv_packet >> total_player >> player_id >> total_question;
    LOG("GAME_INFO", "Total player: " << total_player);
    LOG("GAME_INFO", "Player id: " << player_id);
    LOG("GAME_INFO", "Total question: " << total_question);
}

// receive the question from server
Question Player::receive_question() {
    sf::Packet recv_packet;
    if (socket.receive(recv_packet) != sf::Socket::Done) {
        std::cout << "Error receiving packet" << std::endl;
        return Question();
    }
    Question q;
    recv_packet >> q;
    return q;
}

// skip the question
void Player::skip_question() {
    if (!can_skip)
        return;

    sf::Packet send_packet;
    std::string action = "skip";
    send_packet << action;
    if (socket.send(send_packet) != sf::Socket::Done) {
        std::cout << "Error sending packet" << std::endl;
        return;
    }

    can_skip = false;
}

// send the answer to server
void Player::send_answer(std::string answer) {
    sf::Packet send_packet;
    std::string action = "answer";
    send_packet << action << answer;
    if (socket.send(send_packet) != sf::Socket::Done) {
        std::cout << "Error sending packet" << std::endl;
        return;
    }
}

// Test kakaka
void Player::test() {
    sf::Packet recv_packet;
    if (socket.receive(recv_packet) != sf::Socket::Done) {
        std::cout << "Error receiving packet" << std::endl;
        return;
    }

    Question q;
    recv_packet >> q;
    std::cout << q;
}
