#include "screen.h"

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <thread>

#include "question.h"
extern Player p;
void Screen::drawWelcomeScreen() {
    std::cout << "Ve Welcome Screen ne pri\n";
    this->gui.removeAllWidgets();

    tgui::Button::Ptr startBtn = tgui::Button::create("Start");
    startBtn->setPosition(50, 50);
    startBtn->setSize(200, 50);

    tgui::Button::Ptr exitBtn = tgui::Button::create("Exit");
    exitBtn->setPosition(300, 50);
    exitBtn->setSize(200, 50);

    this->gui.add(startBtn);
    this->gui.add(exitBtn);

    startBtn->onPress([&] { this->drawNamingScreen(); });

    exitBtn->onPress([&] { this->window.close(); });

    std::cout << "Xong Welcome Screen ne pri\n";
}

/*
void register_account(tgui::String name)
{
    p.register_account(name.toStdString());
}
*/

void Screen::drawNamingScreen() {
    std::cout << "GHI TEN DI PRI\n";
    this->gui.removeAllWidgets();

    tgui::EditBox::Ptr nameBox = tgui::EditBox::create();
    nameBox->setSize(600, 85);
    nameBox->setPosition("20%", "20%");

    tgui::Button::Ptr submitBtn = tgui::Button::create("Submit");
    submitBtn->setSize(400, 85);
    submitBtn->setPosition("20%", "60%");

    nameBox->setTextSize(70);
    nameBox->setDefaultText("");  // ko co cai nay thi no se "aaaaaaaaaa" ko hieu tai sao

    this->gui.add(nameBox);
    this->gui.add(submitBtn);
    // nameBox->onReturnKeyPress(&register_account);
    submitBtn->onPress([=] {
                        if (!p.register_account(nameBox->getText().toStdString()))
                            this->drawNamingScreen();
                        else 
                            this->drawWaitingForHostScreen(); });
    std::cout << "XONG HAM NHE PRI\n";
}

void Screen::waitForQuestion() {
    cout << "CHO CAU HOI NE PRI\n";
    Question q = p.receive_question();
    cout << "DOI XONG ROI NE PRI\n";

    this->drawGameScreen(q);
}

void Screen::drawWaitingForHostScreen() {
    std::cout << "DOI TI NHE PRI\n";
    this->gui.removeAllWidgets();
    tgui::ChatBox::Ptr textBox = tgui::ChatBox::create();
    textBox->addLine("WAITING FOR HOST");
    this->gui.add(textBox);

    std::thread t(&Screen::waitForQuestion, this);
    t.detach();
    std::cout << "DOI XONG ROI NHE PRI\n";
}

void Screen::drawGameScreen(Question q) {
    std::cout << "VAO GAME NE PRI\n";
    this->gui.removeAllWidgets();
    std::cout << "LA QUA A NHEN\n";
    std::cout << q << '\n';

    tgui::Button::Ptr buttonA = tgui::Button::create(q.choice_A);
    std::cout << "LA QUA A NHEN CAU A NE\n";
    tgui::Button::Ptr buttonB = tgui::Button::create(q.choice_B);
    std::cout << "LA QUA A NHEN CAU B NE\n";
    tgui::Button::Ptr buttonC = tgui::Button::create(q.choice_C);
    std::cout << "LA QUA A NHEN CAU C NE\n";
    tgui::Button::Ptr buttonD = tgui::Button::create(q.choice_D);
    std::cout << "LA QUA A NHEN CAU D NE\n";
    tgui::Button::Ptr skip = tgui::Button::create("Skip");
    std::cout << "LA QUA A NHEN CAU SKIP NE\n";

    tgui::ChatBox::Ptr questionBox = tgui::ChatBox::create();
    questionBox->addLine(q.title);
    std::cout << "LA QUA A NHEN CAU QUESTIONBOX NE\n";

    std::cout << "CHOI GAME NE PRI\n";

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
    std::cout << "XONG GAME NE PRI\n";

    buttonA->onPress([=] { p.send_answer("A"); });
    buttonB->onPress([=] { p.send_answer("B"); });
    buttonC->onPress([=] { p.send_answer("C"); });
    buttonD->onPress([=] { p.send_answer("D"); });
    skip->onPress([=] { p.send_answer("SKIP"); });
}
