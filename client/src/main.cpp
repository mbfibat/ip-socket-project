#include <iostream>
#include <string>

#include "../include/constant.h"
#include "../include/player.h"
#include "../include/screen.h"

Screen screen;
Player player;
int num_players;
int player_id;
int num_questions;
int wait_action = ACTION_NONE;

int main() {
    sf::RenderWindow window{{WIDTH, HEIGHT}, "Who wants to be a millionaire? (Amogus Extended)"};
    // Get the desktop resolution and position the window in the center of it
    const auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition({(int)(desktop.width - WIDTH) / 2, (int)(desktop.height - HEIGHT) / 2});

    tgui::Gui gui{window};

    screen.bind(&gui, &window);
    screen.drawWelcomeScreen();

    // TODO: Reset player can_skip to true
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            gui.handleEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.handle_socket();

        if (screen.inTimer)
            screen.drawTimerInGameScreen();

        if (screen.inTimer && screen.timer.getElapsedTime().asSeconds() >= TIMER_SEC) {
            screen.inTimer = false;
            screen.timer.restart();
            player.send_answer("nop");
        }

        if (screen.gameWin || screen.gameOver) {
            if (screen.gameWin)
                screen.drawWinScreen();
            else
                screen.drawGameOverScreen();
            if (screen.timer.getElapsedTime().asSeconds() >= 3) {
                screen.gameWin = screen.gameOver = false;
                screen.timer.restart();
                screen.drawWelcomeScreen();
            }
        }

        window.clear();

        gui.draw();

        window.display();
    }
}
