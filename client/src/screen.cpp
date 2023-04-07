#include "../include/screen.h"

void Screen::bind(tgui::Gui *gui, sf::RenderWindow *window) {
    this->gui = gui;
    this->window = window;
}

void Screen::setBackground() {
    // set background
    std::string imagePath = BACKGROUND_IMG_PATH;
    sf::Texture texture;
    if (!texture.loadFromFile(imagePath)) {
        LOG_ERROR("Cannot load background image");
    }
    // use shared pointer incase the font is destroyed before the gui
    std::shared_ptr<tgui::Picture> background = tgui::Picture::create(texture);
    background->setSize("100%", "100%");
    background->setPosition(0, 0);
    gui->add(background);

    std::string fontPath = FONT_PATH;

    // set font for all widgets in gui to Montserrat Regular font (default is Arial)
    // use shared pointer incase the font is destroyed before the gui
    std::shared_ptr<tgui::Font> font = std::make_shared<tgui::Font>(fontPath);
    gui->setFont(*font);
}

void Screen::drawWelcomeScreen() {
    LOG_INFO("Welcome Screen");
    gui->removeAllWidgets();
    setBackground();

    // set title "There is a millionare among us" in the middle of the screen
    std::shared_ptr<tgui::Label> title = tgui::Label::create("There is a millionaire among us");
    title->setPosition("25%", "10%");
    // title->setTextSize(tgui::Gui::getAbsoluteValue(0.05f * tgui::bindHeight(title)));
    title->setTextSize(50);
    title->setSize("66%", "27%");
    title->getRenderer()->setTextColor(sf::Color::White);

    gui->add(title);

    std::shared_ptr<tgui::Button> startBtn = tgui::Button::create("Start");
    startBtn->setPosition("16%", "60%");
    startBtn->setSize("22%", "14%");

    startBtn->getSharedRenderer()->setBackgroundColor(sf::Color::Black);
    startBtn->getSharedRenderer()->setBorderColor(sf::Color::White);
    startBtn->getSharedRenderer()->setBorderColorHover(sf::Color::White);
    startBtn->getSharedRenderer()->setTextColor(sf::Color::White);
    startBtn->getSharedRenderer()->setRoundedBorderRadius(10);
    startBtn->getSharedRenderer()->setBorders(2);
    startBtn->setTextSize(0);

    std::shared_ptr<tgui::Button> exitBtn = tgui::Button::create("Exit");
    exitBtn->setPosition("61%", "60%");
    exitBtn->setSize("22%", "14%");
    exitBtn->setTextSize(0);

    gui->add(startBtn);
    gui->add(exitBtn);

    startBtn->onPress([=] { this->drawNamingScreen(); });
    exitBtn->onPress([=] { window->close(); });

    LOG_INFO("Welcome Screen Done");
}

void Screen::drawNamingScreen() {
    LOG_INFO("Naming Screen");
    gui->removeAllWidgets();
    this->setBackground();

    std::shared_ptr<tgui::EditBox> nameBox = tgui::EditBox::create();
    nameBox->setSize("66%", "19%");
    nameBox->setPosition("17%", "27%");

    nameBox->getRenderer()->setBorders(2);

    nameBox->getRenderer()->setTextColor(sf::Color::White);
    nameBox->getRenderer()->setCaretColor(sf::Color::White);
    nameBox->getRenderer()->setBorderColor(sf::Color::White);
    nameBox->getRenderer()->setBackgroundColor(sf::Color::Black);

    nameBox->getRenderer()->setTextColorFocused(sf::Color::White);
    nameBox->getRenderer()->setCaretColorFocused(sf::Color::White);
    nameBox->getRenderer()->setBorderColorFocused(sf::Color::White);
    nameBox->getRenderer()->setBackgroundColorFocused(sf::Color::Black);

    nameBox->getRenderer()->setCaretColorHover(sf::Color::Black);
    nameBox->getRenderer()->setBorderColorHover(sf::Color::Yellow);
    nameBox->getRenderer()->setBackgroundColorHover(sf::Color{215, 193, 107, 100});

    nameBox->setTextSize(70);
    nameBox->setDefaultText("");  // ko co cai nay thi no se "aaaaaaaaaa" ko hieu tai sao

    std::shared_ptr<tgui::Button> submitBtn = tgui::Button::create("Submit");
    submitBtn->setSize("22%", "14%");
    submitBtn->setPosition("39%", "59%");
    submitBtn->setTextSize(0);

    gui->add(nameBox);
    gui->add(submitBtn);

    /*
    nameBox->getRenderer()->setBackgroundColor(sf::Color::Black);
    nameBox->getRenderer()->setBorderColor(sf::Color::White);
    nameBox->getRenderer()->setBorderColorHover(sf::Color::White);
    nameBox->getRenderer()->setTextColor(sf::Color::White);
    nameBox->getRenderer()->setBackgroundColorFocused(sf::Color::Black);
    nameBox->getRenderer()->setBackgroundColorHover(sf::Color::Black);
    */

    // nameBox->onReturnKeyPress(&register_account);
    submitBtn->onPress([=] {
        std::string name = nameBox->getText().toStdString();
        LOG_INFO("Name: " + name);

        player.send_register_request(name);
        this->drawWaitingForHostScreen();
    });

    LOG_INFO("Naming Screen Done");
}

void Screen::drawWaitingForHostScreen() {
    LOG_INFO("Waiting For Host Start");
    gui->removeAllWidgets();
    this->setBackground();

    std::shared_ptr<tgui::ChatBox> textBox = tgui::ChatBox::create();
    textBox->setTextColor(sf::Color::White);
    textBox->getRenderer()->setBorderColor(sf::Color::Transparent);
    textBox->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    textBox->addLine("WAITING FOR HOST");
    gui->add(textBox);

    textBox->setSize("66%", "27%");
    textBox->setPosition("35%", "40%");
    textBox->setTextSize(50);
    textBox->setLinesStartFromTop(true);

    /*
    textBox->getRenderer()->setBackgroundColor(sf::Color::Black);
    textBox->getRenderer()->setBorderColor(sf::Color::White);
    textBox->setTextColor(sf::Color::White);
    */

    window->clear();
    gui->draw();
    window->display();
}

void Screen::drawGameScreen(Question question) {
    LOG_INFO("Game Screen");
    gui->removeAllWidgets();
    this->setBackground();

    std::shared_ptr<tgui::Button> buttonA = tgui::Button::create(question.choice_A);
    std::shared_ptr<tgui::Button> buttonB = tgui::Button::create(question.choice_B);
    std::shared_ptr<tgui::Button> buttonC = tgui::Button::create(question.choice_C);
    std::shared_ptr<tgui::Button> buttonD = tgui::Button::create(question.choice_D);
    std::shared_ptr<tgui::Button> skip = tgui::Button::create("Skip");

    std::shared_ptr<tgui::ChatBox> timerBox = tgui::ChatBox::create();
    timerBox->setPosition("90%", "10%");

    std::shared_ptr<tgui::ChatBox> questionBox = tgui::ChatBox::create();
    questionBox->setTextColor(sf::Color::White);
    questionBox->getRenderer()->setBorderColor(sf::Color::Transparent);
    questionBox->getRenderer()->setBackgroundColor(sf::Color::Black);
    questionBox->addLine(question.title);

    buttonA->setSize("39%", "14%");
    buttonB->setSize("39%", "14%");
    buttonC->setSize("39%", "14%");
    buttonD->setSize("39%", "14%");
    skip->setSize("12%", "8%");

    buttonA->setTextSize(0);
    buttonB->setTextSize(0);
    buttonC->setTextSize(0);
    buttonD->setTextSize(0);
    skip->setTextSize(0);

    buttonA->setPosition("8%", "56%");
    buttonB->setPosition("50%", "56%");
    buttonC->setPosition("8%", "76%");
    buttonD->setPosition("50%", "76%");
    skip->setPosition("90%", "90%");

    questionBox->setPosition("86%", "82%");

    questionBox->setSize("83%", "47%");
    questionBox->setPosition("8%", "5%");
    questionBox->setTextSize(50);

    questionBox->setLinesStartFromTop(true);

    gui->add(buttonA);
    gui->add(buttonB);
    gui->add(buttonC);
    gui->add(buttonD);
    gui->add(questionBox);

    if (player.can_skip)
        gui->add(skip);

    this->inTimer = true;
    this->timer.restart();

    buttonA->onPress([=] {
        this->inTimer = false;
        this->timer.restart();
        player.send_answer("a");
    });

    buttonB->onPress([=] {
        this->inTimer = false;
        this->timer.restart();
        player.send_answer("b");
    });

    buttonC->onPress([=] {
        this->inTimer = false;
        this->timer.restart();
        player.send_answer("c");
    });

    buttonD->onPress([=] {
        this->inTimer = false;
        this->timer.restart();
        player.send_answer("d");
    });

    skip->onPress([=] {
        this->inTimer = false;
        this->timer.restart();
        player.send_skip_request();
        screen.drawWaitingForHostScreen();
    });

    LOG_INFO("End Turn");
}

void Screen::drawTimerInGameScreen() {
    // remove the last timer
    auto widgets = gui->getWidgets();
    if (!widgets.empty()) {
        auto lastWidget = widgets.back();
        auto lastTimer = std::dynamic_pointer_cast<tgui::ChatBox>(lastWidget);
        if (lastTimer != nullptr)
            gui->remove(lastTimer);
    }

    std::shared_ptr<tgui::ChatBox> textBox = tgui::ChatBox::create();

    textBox->setSize("66%", "27%");
    textBox->setPosition("45%", "25%");
    textBox->setTextSize(60);
    textBox->setTextColor(sf::Color::White);
    textBox->getRenderer()->setBorderColor(sf::Color::Transparent);
    textBox->getRenderer()->setBackgroundColor(sf::Color::Transparent);

    int timeLeft = 31 - timer.getElapsedTime().asSeconds();
    textBox->addLine(std::to_string(timeLeft));
    gui->add(textBox);
}

void Screen::drawWinScreen() {
    // LOG_INFO("Win Screen");
    gui->removeAllWidgets();
    // this->setBackground();

    // set timer to show the screen for only 3 seconds
    gameWin = true;
    // timer.restart();

    // set background
    std::string imagePath = WIN_BACKGROUND_IMG_PATH;
    sf::Texture texture;
    if (!texture.loadFromFile(imagePath)) {
        LOG_ERROR("Cannot load background image");
    }

    // use shared pointer incase the font is destroyed before the gui
    std::shared_ptr<tgui::Picture> background = tgui::Picture::create(texture);
    background->setSize("100%", "100%");
    background->setPosition(0, 0);
    gui->add(background);

    // set position of text box to the lower center of the screen
    std::shared_ptr<tgui::ChatBox> textBox = tgui::ChatBox::create();

    textBox->setSize("66%", "27%");
    textBox->setPosition("23%", "65%");
    textBox->setTextSize(50);
    textBox->setTextColor(sf::Color::Blue);
    textBox->getRenderer()->setBorderColor(sf::Color::Transparent);
    textBox->getRenderer()->setBackgroundColor(sf::Color::Transparent);

    int timeLeft = 4 - timer.getElapsedTime().asSeconds();
    std::string s = "RETURN TO MAIN LOBBY IN " + std::to_string(timeLeft) + " SECONDS";
    textBox->addLine(s);
    gui->add(textBox);

    // std::shared_ptr<tgui::Button> button = tgui::Button::create("Play Again");
    // button->setSize("12%", "8%");
    // button->setPosition("90%", "90%");
    // button->setTextSize(0);
    // gui->add(button);

    // button->onPress([=] {
    //     screen.drawNamingScreen();
    // });

    window->clear();
    gui->draw();
    window->display();
}

void Screen::drawGameOverScreen() {
    // LOG_INFO("Game Over Screen");
    gui->removeAllWidgets();
    // this->setBackground();

    // set timer to show the screen for only 3 seconds
    gameOver = true;
    // timer.restart();

    // set background
    std::string imagePath = LOSE_BACKGROUND_IMG_PATH;
    sf::Texture texture;
    if (!texture.loadFromFile(imagePath)) {
        LOG_ERROR("Cannot load background image");
    }

    // use shared pointer incase the font is destroyed before the gui
    std::shared_ptr<tgui::Picture> background = tgui::Picture::create(texture);
    background->setSize("100%", "100%");
    background->setPosition(0, 0);
    gui->add(background);

    // set position of text box to the lower center of the screen
    std::shared_ptr<tgui::ChatBox> textBox = tgui::ChatBox::create();
    textBox->setSize("66%", "27%");
    textBox->setPosition("23%", "65%");
    textBox->setTextSize(50);
    textBox->setTextColor(sf::Color::Red);
    textBox->getRenderer()->setBorderColor(sf::Color::Transparent);
    textBox->getRenderer()->setBackgroundColor(sf::Color::Transparent);

    int timeLeft = 4 - timer.getElapsedTime().asSeconds();
    std::string s = "RETURN TO MAIN LOBBY IN " + std::to_string(timeLeft) + " SECONDS";
    textBox->addLine(s);
    gui->add(textBox);

    window->clear();
    gui->draw();
    window->display();
}

void Screen::playCorrectSound() {
    if (!buffer.loadFromFile(CORRECT_SOUND_PATH)) {
        LOG_INFO("Cannot load correct sound");
    }
    sound.setBuffer(buffer);
    sound.setVolume(100);
    sound.play();
    LOG_INFO("play correct sound");
}

void Screen::playWrongSound() {
    if (!buffer.loadFromFile(INCORRECT_SOUND_PATH)) {
        LOG_INFO("Cannot load wrong sound");
    }
    sound.setBuffer(buffer);
    sound.setVolume(100);
    sound.play();
    LOG_INFO("play wrong sound");
}

void Screen::animateCorrectAns() {
}