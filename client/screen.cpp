#include "screen.h"

#include <unistd.h>

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "question.h"
extern Player p;
void Screen::setBackground() {
    // get current directory for file path
    char cwd[101];
    std::string filePath;
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        filePath = std::string(cwd);
    } else {
        perror("getcwd() error");
    }

    // set background
    std::string imagePath = filePath + "/assets/image/background.png";
    sf::Texture texture;
    if (!texture.loadFromFile(imagePath)) {
        std::cout << "Error loading background image\n";
    }
    // use shared pointer incase the font is destroyed before the gui
    std::shared_ptr<tgui::Picture> background = tgui::Picture::create(texture);
    this->gui.add(background);

    std::string fontPath = filePath + "/assets/fonts/Montserrat-Regular.ttf";

    // set font for all widgets in gui to Montserrat Regular font (default is Arial)
    // use shared pointer incase the font is destroyed before the gui
    std::shared_ptr<tgui::Font> font = std::make_shared<tgui::Font>(fontPath);
    this->gui.setFont(*font);
}

void Screen::drawWelcomeScreen() {
    this->gui.removeAllWidgets();

    this->setBackground();
    std::cout << "Ve Welcome Screen ne pri\n";

    std::shared_ptr<tgui::Button> startBtn = tgui::Button::create("Start");
    startBtn->setPosition(50, 50);
    startBtn->setSize(200, 50);

    std::shared_ptr<tgui::Button> exitBtn = tgui::Button::create("Exit");
    exitBtn->setPosition(300, 50);
    exitBtn->setSize(200, 50);

    startBtn->getRenderer()->setBackgroundColor(sf::Color::Blue);

    this->gui.add(startBtn);
    this->gui.add(exitBtn);

    startBtn->onPress([&] { this->drawNamingScreen(); });

    exitBtn->onPress([&] { this->window.close(); });

    std::cout << "Xong Welcome Screen ne pri\n";
}

void Screen::drawNamingScreen() {
    std::cout << "GHI TEN DI PRI\n";
    this->gui.removeAllWidgets();
    this->setBackground();

    std::shared_ptr<tgui::EditBox> nameBox = tgui::EditBox::create();
    nameBox->setSize(600, 85);
    nameBox->setPosition("20%", "20%");

    std::shared_ptr<tgui::Button> submitBtn = tgui::Button::create("Submit");
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
    cout << "CO CAU HOI ROI NE PRI\n";
    cout << q << '\n';

    this->drawGameScreen(q);
}

void Screen::drawWaitingForHostScreen() {
    std::cout << "DOI TI NHE PRI\n";
    this->gui.removeAllWidgets();
    this->setBackground();
    std::cout << "SET BACKGROUND XONG ROI NHE PRI\n";

    std::shared_ptr<tgui::ChatBox> textBox = tgui::ChatBox::create();
    textBox->addLine("WAITING FOR HOST");
    this->gui.add(textBox);

    std::cout << "CHAY DEN DAY ROI NHE PRI\n";
    std::thread t(&Screen::waitForQuestion, this);
    t.detach();
    std::cout << "DOI XONG ROI NHE PRI\n";
}

void Screen::drawGameScreen(Question q) {
    std::cout << "VAO GAME NE PRI\n";
    this->gui.removeAllWidgets();
    this->setBackground();

    std::cout << "LA QUA A NHEN\n";

    std::shared_ptr<tgui::Button> buttonA = tgui::Button::create(q.choice_A);
    std::shared_ptr<tgui::Button> buttonB = tgui::Button::create(q.choice_B);
    std::shared_ptr<tgui::Button> buttonC = tgui::Button::create(q.choice_C);
    std::shared_ptr<tgui::Button> buttonD = tgui::Button::create(q.choice_D);
    std::shared_ptr<tgui::Button> skip = tgui::Button::create("Skip");

    std::shared_ptr<tgui::ChatBox> timerBox = tgui::ChatBox::create();
    timerBox->setPosition("90%", "10%");

    std::shared_ptr<tgui::ChatBox> questionBox = tgui::ChatBox::create();
    questionBox->addLine(q.title);

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

    buttonA->onPress([=] { 
        p.send_answer("A"); 
        string result = p.receive_answer_result();
        if (result == "CORRECT") {
            this->drawWaitingForHostScreen(); 
        } else {
            //this->drawGameOverScreen(); Ve con amogus
        } });

    buttonB->onPress([=] { 
        p.send_answer("B"); 
        string result = p.receive_answer_result();
        if (result == "CORRECT") {
            this->drawWaitingForHostScreen(); 
        } else {
            //this->drawGameOverScreen(); Ve con amogus
        } });

    buttonC->onPress([=] {
        p.send_answer("C"); 
        string result = p.receive_answer_result();
        if (result == "CORRECT") {
            this->drawWaitingForHostScreen(); 
        } else {
            //this->drawGameOverScreen(); Ve con amogus
        } });

    buttonD->onPress([=] {
        p.send_answer("D"); 
        string result = p.receive_answer_result();
        if (result == "CORRECT") {
            this->drawWaitingForHostScreen(); 
        } else {
            //this->drawGameOverScreen(); Ve con amogus
        } });

    // TODO: Chỉ skip được nếu biến can_skip = true
    skip->onPress([=] { p.send_answer("SKIP"); });

    int remaining_time = 2;
    this->gui.add(timerBox);
    while (remaining_time >= 0) {
        cout << "Remaining time: " << remaining_time << '\n';
        timerBox->removeAllLines();
        timerBox->addLine(std::to_string(remaining_time));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        remaining_time--;
    }
    auto par = timerBox->getParent();
    cout << "Parent: " << par << '\n';
    if (par != nullptr) {
        p.send_answer("NOP");
        std::string result = p.receive_answer_result();
        this->drawWaitingForHostScreen();
    }
}

// TODO: DrawGameOverScreen
// TODO: DrawWinScreen