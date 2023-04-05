#ifndef SCREEN_H
#define SCREEN_H

#include <unistd.h>

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <functional>
#include <iostream>

#include "logger.h"
#include "player.h"
#include "question.h"

class Screen {
private:
    tgui::Gui *gui;
    sf::RenderWindow *window;

public:
    sf::Clock timer;
    bool inTimer = false;

    // Screen(tgui::Gui &gui, sf::RenderWindow &window) : gui(gui), window(window){};
    void bind(tgui::Gui *gui, sf::RenderWindow *window);

    void setBackground();
    void drawWelcomeScreen();
    void drawNamingScreen();
    void drawWaitingForHostScreen();
    void drawGameScreen(Question q);
    void drawWinScreen();
    void drawGameOverScreen();
};

extern Screen screen;

#endif  // SCREEN_H