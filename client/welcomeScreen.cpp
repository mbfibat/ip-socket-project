#include "welcomeScreen.h"
// #include "gameScreen.h"
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

void drawWelcomeScreen(tgui::Gui &gui, sf::RenderWindow &window)
{

    gui.removeAllWidgets();

    tgui::Button::Ptr startBtn = tgui::Button::create("Start");
    startBtn->setPosition(50, 50);
    startBtn->setSize(200, 50);

    tgui::Button::Ptr exitBtn = tgui::Button::create("Exit");
    exitBtn->setPosition(300, 50);
    exitBtn->setSize(200, 50);

    gui.add(startBtn);
    gui.add(exitBtn);

    startBtn->onPress([&]
                      { drawNamingScreen(gui); });

    exitBtn->onPress([&]
                     { window.close(); });
}

void drawNamingScreen(tgui::Gui &gui)
{

    gui.removeAllWidgets();

    tgui::EditBox::Ptr editBox = tgui::EditBox::create();
    editBox->setSize(600, 85);
    editBox->setPosition("20%", "20%");

    tgui::Button::Ptr submitBtn = tgui::Button::create("Submit");
    submitBtn->setSize(400, 85);
    submitBtn->setPosition("20%", "60%");

    editBox->setTextSize(70);

    gui.add(editBox);
    gui.add(submitBtn);

    // submitBtn->onPress([&]{ drawGameScreen(gui); });
}