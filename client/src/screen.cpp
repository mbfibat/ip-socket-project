#include "../include/screen.h"

void Screen::setBackground() {
    // set background
    std::string imagePath = BACKGROUND_IMG_PATH;
    sf::Texture texture;
    if (!texture.loadFromFile(imagePath)) {
        LOG_ERROR("Cannot load background image");
    }
    // use shared pointer incase the font is destroyed before the gui
    std::shared_ptr<tgui::Picture> background = tgui::Picture::create(texture);
    this->gui.add(background);

    std::string fontPath = FONT_PATH;

    // set font for all widgets in gui to Montserrat Regular font (default is Arial)
    // use shared pointer incase the font is destroyed before the gui
    std::shared_ptr<tgui::Font> font = std::make_shared<tgui::Font>(fontPath);
    this->gui.setFont(*font);
}

void Screen::drawWelcomeScreen() {
    this->gui.removeAllWidgets();

    this->setBackground();
    LOG_INFO("Welcome Screen");

    std::shared_ptr<tgui::Button> startBtn = tgui::Button::create("Start");
    startBtn->setPosition(50, 50);
    startBtn->setSize(200, 50);

    std::shared_ptr<tgui::Button> exitBtn = tgui::Button::create("Exit");
    exitBtn->setPosition(300, 50);
    exitBtn->setSize(200, 50);

    startBtn->getRenderer()->setBackgroundColor(sf::Color::Blue);

    this->gui.add(startBtn);
    this->gui.add(exitBtn);

    startBtn->onPress([=] { this->drawNamingScreen(); });

    exitBtn->onPress([=] { this->window.close(); });

    LOG_INFO("Welcome Screen Done");
}

void Screen::drawNamingScreen() {
    LOG_INFO("Naming Screen");
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
        std::string name = nameBox->getText().toStdString();
        LOG_INFO("Name: " + name);

        auto [code, msg] = player.register_account(name);
        if (code != CODE_SUCCESS)
            this->drawNamingScreen();
        else {
            this->drawWaitingForHostScreen();
        } });

    LOG_INFO("Naming Screen Done");
}

void Screen::drawWaitingForHostScreen() {
    LOG_INFO("Waiting For Host Start");
    this->gui.removeAllWidgets();
    this->setBackground();

    std::shared_ptr<tgui::ChatBox> textBox = tgui::ChatBox::create();
    textBox->addLine("WAITING FOR HOST");
    this->gui.add(textBox);

    this->window.clear();
    this->gui.draw();
    this->window.display();

    player.receive_game_info();
    Question question = player.receive_question();
    LOG_INFO("Receive question: " << question);
    this->drawGameScreen(question);
}

void Screen::drawGameScreen(Question question) {
    LOG_INFO("Game Screen");
    this->gui.removeAllWidgets();
    this->setBackground();

    std::shared_ptr<tgui::Button> buttonA = tgui::Button::create(question.choice_A);
    std::shared_ptr<tgui::Button> buttonB = tgui::Button::create(question.choice_B);
    std::shared_ptr<tgui::Button> buttonC = tgui::Button::create(question.choice_C);
    std::shared_ptr<tgui::Button> buttonD = tgui::Button::create(question.choice_D);
    std::shared_ptr<tgui::Button> skip = tgui::Button::create("Skip");

    std::shared_ptr<tgui::ChatBox> timerBox = tgui::ChatBox::create();
    timerBox->setPosition("90%", "10%");

    std::shared_ptr<tgui::ChatBox> questionBox = tgui::ChatBox::create();
    questionBox->addLine(question.title);

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

    if (player.can_skip)
        this->gui.add(skip);

    this->inTimer = true;
    this->timer.restart();

    buttonA->onPress([=] {
        this->inTimer = false;
        auto [code, msg] = player.send_answer("a");
        if (code == CODE_WIN) {
            this->drawWinScreen();
        } else if (code == CODE_CORRECT) {
            // this->drawWaitingForHostScreen();
            Question question = player.receive_question();
            LOG_INFO("Receive question: " << question);
            this->drawGameScreen(question);
        } else {
            this->drawGameOverScreen();
        }
    });

    buttonB->onPress([=] {
        this->inTimer = false;
        auto [code, msg] = player.send_answer("b");
        if (code == CODE_WIN) {
            this->drawWinScreen();
        } else if (code == CODE_CORRECT) {
            // this->drawWaitingForHostScreen();
            Question question = player.receive_question();
            LOG_INFO("Receive question: " << question);
            this->drawGameScreen(question);
        } else {
            this->drawGameOverScreen();
        }
    });

    buttonC->onPress([=] {
        this->inTimer = false;
        auto [code, msg] = player.send_answer("c");
        if (code == CODE_WIN) {
            this->drawWinScreen();
        } else if (code == CODE_CORRECT) {
            // this->drawWaitingForHostScreen();
            Question question = player.receive_question();
            LOG_INFO("Receive question: " << question);
            this->drawGameScreen(question);
        } else {
            this->drawGameOverScreen();
        }
    });

    buttonD->onPress([=] {
        this->inTimer = false;
        auto [code, msg] = player.send_answer("d");
        if (code == CODE_WIN) {
            this->drawWinScreen();
        } else if (code == CODE_CORRECT) {
            // this->drawWaitingForHostScreen();
            Question question = player.receive_question();
            LOG_INFO("Receive question: " << question);
            this->drawGameScreen(question);
        } else {
            this->drawGameOverScreen();
        }
    });

    skip->onPress([=] {
        this->inTimer = false;
        player.can_skip = false;
        auto [code, msg] = player.skip_question();
        if (code == CODE_SUCCESS) {
            // this->drawWaitingForHostScreen();
            // TODO: thêm waiting screen khác
            // không dùng lại waiting for host được vì nó có receive game info
            // nếu không thì sẽ kẹt ở screen này đến khi nhận được question
            Question question = player.receive_question();
            LOG_INFO("Receive question: " << question);
            this->drawGameScreen(question);
        } else {
            this->drawGameOverScreen();
        } });

    LOG_INFO("End Turn");
}

void Screen::drawWinScreen() {
    LOG_INFO("Win Screen");
    this->gui.removeAllWidgets();
    this->setBackground();

    std::shared_ptr<tgui::ChatBox> textBox = tgui::ChatBox::create();
    textBox->addLine("YOU WIN");
    this->gui.add(textBox);

    this->window.clear();
    this->gui.draw();
    this->window.display();
}

void Screen::drawGameOverScreen() {
    LOG_INFO("Game Over Screen");
    this->gui.removeAllWidgets();
    this->setBackground();

    std::shared_ptr<tgui::ChatBox> textBox = tgui::ChatBox::create();
    textBox->addLine("GAME OVER");
    this->gui.add(textBox);

    this->window.clear();
    this->gui.draw();
    this->window.display();
}
