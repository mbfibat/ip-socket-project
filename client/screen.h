#ifndef screen_h
#define screen_h
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
class Screen
{
private:
    tgui::Gui &gui;
    sf::RenderWindow &window;
    tgui::String name;

public:
    Screen(tgui::Gui &gui, sf::RenderWindow &window) : gui(gui), window(window){};
    void drawWelcomeScreen();
    void drawNamingScreen();
    void drawGameScreen();
};
#endif