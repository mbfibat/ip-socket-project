#include "welcomeScreen.h"
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

void drawWelcomeScreen(tgui::Gui& gui) {
    gui.removeAllWidgets();
    tgui::Button::Ptr button = tgui::Button::create("text button");
    gui.add(button);
}
