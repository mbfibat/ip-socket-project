#include "main.h"

#include <iostream>
#include <string>

int main()
{
    std::string name;
    std::cin >> name;

    Player p;
    p.register_account(name);

    /*
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

    // tgui::Button::Ptr button = tgui::Button::create("text button");
    // gui.add(button);
    // drawWelcomeScreen(gui, window);
    Screen screen(gui, window);
    screen.drawWelcomeScreen();

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