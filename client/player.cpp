#include "player.h"

const static int PORT = 5000;
const static std::string IP = "127.0.0.1";

Player::Player() {
    sf::Socket::Status status = socket.connect(IP, PORT);
    if (status != sf::Socket::Done) {
        std::cout << "Error connecting to server" << std::endl;
        return;
    }
    std::cout << "Connected to server" << std::endl;
}

// Register a nickname for the player and send it to the server
// Return true if the nickname is valid and not taken
// Return false if the nickname is invalid or taken
// The name is valid if regex ^[a-zA-Z0-9_]{1,10}$ matches
// The name is taken if the server returns a boolean false
bool Player::register_account(std::string& name) {
    sf::Packet send_packet;
    std::string action = "register";
    send_packet << action << name;
    if (socket.send(send_packet) != sf::Socket::Done) {
        std::cout << "Error sending packet" << std::endl;
        return false;
    }

    sf::Packet recv_packet;
    if (socket.receive(recv_packet) != sf::Socket::Done) {
        std::cout << "Error receiving packet" << std::endl;
        return false;
    }

    bool is_valid;
    recv_packet >> is_valid;
    return is_valid;
}

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