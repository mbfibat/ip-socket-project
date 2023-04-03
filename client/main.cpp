#include "main.h"

#include <iostream>
#include <string>

Player p;

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

    if (!p.connect())
        return 0;

    sf::RenderWindow window{{WIDTH, HEIGHT}, "TGUI example - SFML_GRAPHICS backend"};
    // Get the desktop resolution and position the window in the center of it
    const auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition({(int)(desktop.width - WIDTH) / 2, (int)(desktop.height - HEIGHT) / 2});

    tgui::Gui gui{window};

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