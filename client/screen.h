#ifndef screen_h
#define screen_h
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "player.h"
#include "question.h"
using namespace std;

class Screen {
private:
    tgui::Gui &gui;
    sf::RenderWindow &window;

public:
    string name;  // player inputted name
    Screen(tgui::Gui &gui, sf::RenderWindow &window) : gui(gui), window(window){};
    void drawWelcomeScreen();
    void drawNamingScreen();
    void drawWaitingForHostScreen();

    void waitForQuestion();
    void drawGameScreen(Question q);
};

void register_account(tgui::String name);

#endif