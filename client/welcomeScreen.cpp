#include "welcomeScreen.h"

void drawWelcomeScreen(tgui::Gui& gui) {
    gui.removeAllWidgets();
    tgui::Button::Ptr button = tgui::Button::create("text button");
    gui.add(button);
}
