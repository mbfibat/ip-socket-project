#include "screen.h"
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

void Screen::drawWelcomeScreen()
{

    this->gui.removeAllWidgets();

    tgui::Button::Ptr startBtn = tgui::Button::create("Start");
    startBtn->setPosition(50, 50);
    startBtn->setSize(200, 50);

    tgui::Button::Ptr exitBtn = tgui::Button::create("Exit");
    exitBtn->setPosition(300, 50);
    exitBtn->setSize(200, 50);

    this->gui.add(startBtn);
    this->gui.add(exitBtn);

    startBtn->onPress([&]
                      { this->drawNamingScreen(); });

    exitBtn->onPress([&]
                     { this->window.close(); });
}
void Screen::drawNamingScreen()
{
    this->gui.removeAllWidgets();

    tgui::EditBox::Ptr nameBox = tgui::EditBox::create();
    nameBox->setSize(600, 85);
    nameBox->setPosition("20%", "20%");

    tgui::Button::Ptr submitBtn = tgui::Button::create("Submit");
    submitBtn->setSize(400, 85);
    submitBtn->setPosition("20%", "60%");

    nameBox->setTextSize(70);
    nameBox->setDefaultText(""); // ko co cai nay thi no se "aaaaaaaaaa" ko hieu tai sao

    this->gui.add(nameBox);
    this->gui.add(submitBtn);

    nameBox->setFocused(true);
    // submitBtn->onPress([&]
    //                    { this->drawGameScreen(); });
    submitBtn->onPress([&]
                       {
                           if (nameBox->isFocused())
                               this->name = nameBox->getText();
                           else
                               cout << "error here";

                           //  stdname = name.toStdString();
                           //  std::cout << "Text entered: " << stdname << std::endl;
                       });
}

void Screen::drawGameScreen()
{

    this->gui.removeAllWidgets();

    tgui::Button::Ptr buttonA = tgui::Button::create("A");
    tgui::Button::Ptr buttonB = tgui::Button::create("B");
    tgui::Button::Ptr buttonC = tgui::Button::create("C");
    tgui::Button::Ptr buttonD = tgui::Button::create("D");

    tgui::ChatBox::Ptr questionBox = tgui::ChatBox::create();

    buttonA->setSize(200, 50);
    buttonB->setSize(200, 50);
    buttonC->setSize(200, 50);
    buttonD->setSize(200, 50);

    buttonA->setPosition("10%", "50%");
    buttonB->setPosition("50%", "50%");
    buttonC->setPosition("10%", "70%");
    buttonD->setPosition("50%", "70%");

    questionBox->setPosition("10%", "20%");

    this->gui.add(buttonA);
    this->gui.add(buttonB);
    this->gui.add(buttonC);
    this->gui.add(buttonD);
    this->gui.add(questionBox);
}