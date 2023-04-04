#include "../include/main.h"

#include <iostream>
#include <string>

Player p;

int main() {
    if (!p.connect())
        return 0;

    sf::RenderWindow window{{WIDTH, HEIGHT}, "TGUI example - SFML_GRAPHICS backend"};
    // Get the desktop resolution and position the window in the center of it
    const auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition({(int)(desktop.width - WIDTH) / 2, (int)(desktop.height - HEIGHT) / 2});

    tgui::Gui gui{window};

    Screen screen(gui, window);
    screen.drawWelcomeScreen();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            gui.handleEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (screen.inTimer)
            std::cout << screen.timer.getElapsedTime().asSeconds() << " s" << std::endl;
        if (screen.inTimer && screen.timer.getElapsedTime().asSeconds() >= 10) {
            screen.inTimer = false;
            screen.timer.restart();
            p.send_answer("NOP");
            int RETURN_CODE = p.receive_answer_result();

            if (RETURN_CODE == CODE_WIN)
                screen.drawWinScreen();
            else if (RETURN_CODE == CODE_LOSE)
                screen.drawGameOverScreen();
        }

        window.clear();

        gui.draw();

        window.display();
    }
}