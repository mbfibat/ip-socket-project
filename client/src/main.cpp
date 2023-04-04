#include <iostream>
#include <string>

#include "../include/constant.h"
#include "../include/player.h"
#include "../include/screen.h"

Player player;
int num_players;
int player_id;
int num_questions;

int main() {
    sf::RenderWindow window{{WIDTH, HEIGHT}, "Who wants to be a millionaire? phien ban amogus"};
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

        // if (screen.inTimer)
        //     std::cout << screen.timer.getElapsedTime().asSeconds() << " s" << std::endl;
        if (screen.inTimer && screen.timer.getElapsedTime().asSeconds() >= TIMER_SEC) {
            screen.inTimer = false;
            screen.timer.restart();

            auto [code, msg] = player.send_answer("NOP");
            if (code == CODE_WIN)
                screen.drawWinScreen();
            else if (code == CODE_LOSE)
                screen.drawGameOverScreen();
        }

        window.clear();

        gui.draw();

        window.display();
    }
}