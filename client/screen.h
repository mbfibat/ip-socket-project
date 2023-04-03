#ifndef screen_h
#define screen_h
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include "player.h"
using namespace std;

class Screen
{
private:
    tgui::Gui &gui;
    sf::RenderWindow &window;

public:
    string name; // player inputted name
    Screen(tgui::Gui &gui, sf::RenderWindow &window) : gui(gui), window(window){};
    void drawWelcomeScreen();
    void drawNamingScreen();
    void drawGameScreen();
};

#endif