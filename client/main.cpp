#include "main.h"

#include <iostream>
#include <string>
extern Player p;
int main() {
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

    if (!p.connect()) return 0;

    sf::RenderWindow window{{800, 600}, "TGUI example - SFML_GRAPHICS backend"};
    tgui::Gui gui{window};

    // tgui::Button::Ptr button = tgui::Button::create("text button");
    // gui.add(button);
    // drawWelcomeScreen(gui, window);
    cout << "checkpt1";
    Screen screen(gui, window);
    screen.drawWelcomeScreen();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            gui.handleEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        gui.draw();

        window.display();
    }
}