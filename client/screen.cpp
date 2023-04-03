#include "screen.h"
#include "question.h"
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
extern Player p;
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

void register_account(tgui::String name)
{
    p.register_account(name.toStdString());
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
    nameBox->onReturnKeyPress(&register_account);
    submitBtn->onPress([=]()
                       {std::cout<<"adsfasdf"; 
                        p.register_account(nameBox->getText().toStdString());});
                        //this->drawWaitingForHostScreen(); });
}

void Screen::drawWaitingForHostScreen()
{
    std::cout << "zzzz";
    this->gui.removeAllWidgets();
    tgui::ChatBox::Ptr textBox = tgui::ChatBox::create();
    textBox->addLine("WAITING FOR HOST");
    this->gui.add(textBox);
    Question q = p.receive_question();
    this->drawGameScreen(q);
}

void Screen::drawGameScreen(Question q)
{

    this->gui.removeAllWidgets();

    tgui::Button::Ptr buttonA = tgui::Button::create(q.choice_A);
    tgui::Button::Ptr buttonB = tgui::Button::create(q.choice_B);
    tgui::Button::Ptr buttonC = tgui::Button::create(q.choice_C);
    tgui::Button::Ptr buttonD = tgui::Button::create(q.choice_D);
    tgui::Button::Ptr skip = tgui::Button::create("Skip");

    tgui::ChatBox::Ptr questionBox = tgui::ChatBox::create();
    questionBox->addLine(q.title);

    buttonA->setSize(200, 50);
    buttonB->setSize(200, 50);
    buttonC->setSize(200, 50);
    buttonD->setSize(200, 50);

    buttonA->setPosition("10%", "50%");
    buttonB->setPosition("50%", "50%");
    buttonC->setPosition("10%", "70%");
    buttonD->setPosition("50%", "70%");
    skip->setPosition("90%", "90%");

    questionBox->setPosition("10%", "20%");

    this->gui.add(buttonA);
    this->gui.add(buttonB);
    this->gui.add(buttonC);
    this->gui.add(buttonD);
    this->gui.add(questionBox);
    this->gui.add(skip);
}
