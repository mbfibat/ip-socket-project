#include "player.h"

Player p;
const static int PORT = 5000;
const static std::string IP = "127.0.0.1";

// Connect to server, if server is not open return false
bool Player::connect()
{
    // socket.setBlocking(false);
    selector.add(socket);
    sf::Socket::Status status = socket.connect(IP, PORT);
    sf::sleep(sf::milliseconds(100));
    while (status == sf::Socket::NotReady)
    {
        // Connection in progress, wait for a little while
        sf::sleep(sf::milliseconds(100));

        // Check the connection status again
        status = socket.connect(IP, PORT);
    }
    if (status != sf::Socket::Done)
    {
        std::cout << "Error connecting to server" << std::endl;
        return false;
    }
    std::cout << "Connected to server" << std::endl;
    return true;
}

// Register a nickname for the player and send it to the server
// Return true if the nickname is valid and not taken
// Return false if the nickname is invalid or taken
// The name is valid if regex ^[a-zA-Z0-9_]{1,10}$ matches
// The name is taken if the server returns a boolean false
bool Player::register_account(std::string name)
{
    sf::Packet send_packet;
    std::string action = "register";
    send_packet << action << name;
    if (socket.send(send_packet) != sf::Socket::Done)
    {
        std::cout << "Error sending packet" << std::endl;
        return false;
    }

    sf::Packet recv_packet;
    if (socket.receive(recv_packet) != sf::Socket::Done)
    {
        std::cout << "Error receiving packet" << std::endl;
        return false;
    }

    bool is_valid;
    recv_packet >> is_valid;
    return is_valid;
}

// receive the question from server
Question Player::receive_question()
{
    while (true)
    { // Polling for question
        if (!selector.isReady(socket))
            continue;

        sf::Packet recv_packet;
        if (socket.receive(recv_packet) != sf::Socket::Done)
        {
            std::cout << "Error receiving packet" << std::endl;
            return Question();
        }
        Question q;
        recv_packet >> q;
        return q;
    }
}

// skip the question
void Player::skip_question()
{
    if (!can_skip)
        return;

    sf::Packet send_packet;
    std::string action = "skip";
    send_packet << action;
    if (socket.send(send_packet) != sf::Socket::Done)
    {
        std::cout << "Error sending packet" << std::endl;
        return;
    }

    can_skip = false;
}

// send the answer to server
void Player::send_answer(std::string answer)
{
    sf::Packet send_packet;
    std::string action = "answer";
    send_packet << action << answer;
    if (socket.send(send_packet) != sf::Socket::Done)
    {
        std::cout << "Error sending packet" << std::endl;
        return;
    }
}

// Test kakaka
void Player::test()
{
    sf::Packet recv_packet;
    if (socket.receive(recv_packet) != sf::Socket::Done)
    {
        std::cout << "Error receiving packet" << std::endl;
        return;
    }

    Question q;
    recv_packet >> q;
    std::cout << q;
}
