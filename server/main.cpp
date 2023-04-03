#include <SFML/Network.hpp>
#include <iostream>
#include <string>

#include "constant.h"
#include "question.h"

#define perr(result, msg)              \
    if (result != sf::Socket::Done) {  \
        std::cout << msg << std::endl; \
        return 1;                      \
    }

int main() {
    sf::TcpListener listener;
    perr(listener.listen(PORT), "Error listening on port " << PORT);

    sf::TcpSocket client;
    perr(listener.accept(client), "Error accepting client");

    Question q;
    q.title = "Which one is the nhentai code for metamorphosis?";
    q.choice_A = "177013";
    q.choice_B = "177014";
    q.choice_C = "177015";
    q.choice_D = "177016";

    sf::Packet send_packet;
    send_packet << q;
    perr(client.send(send_packet), "Error sending packet");
}