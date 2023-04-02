#include <string>
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "main.h"


int main()
{
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect(IP, PORT);
    if (status != sf::Socket::Done) {
        std::cout << "Error connecting to server" << std::endl;
        return 1;
    }

    sf::Packet recv_packet;
    if (socket.receive(recv_packet) != sf::Socket::Done) {
        std::cout << "Error receiving packet" << std::endl;
        return 1;
    }

    Question q;
    recv_packet >> q;
    std::cout << q;

    /*
    Player p;

    p.register_account();

    while (1)
    {
        p.receive_game_info();

        while (1)
        {
            if (p.is_alive)
            {
                p.receive_question();
                p.answer_question();

                p.receive_answer_status();
            }
            else
            {
                p.receive_game_result();
                break;
            }
        }
    }
    */

    sf::RenderWindow window{{800, 600}, "TGUI example - SFML_GRAPHICS backend"};
    tgui::Gui gui{window};

    tgui::Button::Ptr button = tgui::Button::create("text button");
    gui.add(button);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            gui.handleEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        gui.draw();

        window.display();
    }


}