#include <string>
#include <iostream>
#include <SFML/Network.hpp>

const std::string IP = "127.0.0.1";
const int PORT = 5000;

struct Question {
    std::string title;
    std::string choice_A, choice_B, choice_C, choice_D;
};

sf::Packet& operator <<(sf::Packet& packet, const Question& q) {
    return packet << q.title << q.choice_A << q.choice_B << q.choice_C << q.choice_D;
}

int main()
{
    sf::TcpListener listener;
    if (listener.listen(PORT) != sf::Socket::Done) {
        std::cout << "Error listening to port " << PORT << std::endl;
        return 1;
    }
    
    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done) {
        std::cout << "Error accepting client" << std::endl;
        return 1;
    }

    Question q;
    q.title = "Which one is the nhentai code for metamorphosis?";
    q.choice_A = "177013";
    q.choice_B = "177014";
    q.choice_C = "177015";
    q.choice_D = "177016";

    sf::Packet send_packet;
    send_packet << q;
    if (client.send(send_packet) != sf::Socket::Done) {
        std::cout << "Error sending packet" << std::endl;
        return 1;
    }
}