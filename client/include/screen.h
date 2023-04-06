#ifndef SCREEN_H
#define SCREEN_H

#include <unistd.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <functional>
#include <iostream>

#include "logger.h"
#include "player.h"
#include "question.h"
#include "socket.h"

class Screen {
private:
    sf::RenderWindow *window;

public:
    tgui::Gui *gui;
    sf::Clock timer;
    bool inTimer = false;
    bool gameWin = false;
    bool gameOver = false;

    sf::Sound sound;
    sf::SoundBuffer buffer;

    // Screen(tgui::Gui &gui, sf::RenderWindow &window) : gui(gui), window(window){};
    void bind(tgui::Gui *gui, sf::RenderWindow *window);

    void setBackground();
    void drawWelcomeScreen();
    void drawNamingScreen();
    void drawWaitingForHostScreen();
    void drawGameScreen(Question q);
    void drawWinScreen();
    void drawGameOverScreen();
    void playCorrectSound();
    void playWrongSound();
    void animateCorrectAns();
};

extern Screen screen;

#endif  // SCREEN_H