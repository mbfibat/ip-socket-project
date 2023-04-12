#include "../include/game.h"

bool Game::isValidName(std::string name) {
    // check if name exist
    for (auto &player : players) {
        if (player != NULL && player->name == name) {
            return false;
        }
    }
    return std::regex_match(name, std::regex(name_pattern));
}

bool Game::isAllPlayerRegistered() {
    for (auto &player : players) {
        if (player == NULL || !player->registered) {
            return false;
        }
    }
    return true;
}

int Game::countAlivePlayer() {
    int count = 0;
    for (auto &player : players) {
        if (player != NULL) {
            count++;
        }
    }
    return count;
}

Response Game::registerPlayer(std::string name, Player *&player) {
    if (!isValidName(name)) {
        LOG_INFO("Invalid name: " << name);
        return Response{CODE_ERROR, "Invalid name"};
    }

    // Add player
    player->name = name;
    player->registered = true;

    LOG_INFO("Player " << name << " registered");
    return Response{CODE_SUCCESS, "Registered"};
}

void Game::gameStart() {
    LOG_INFO("Game start");

    // Init game
    currentPlayer = 0;
    currentQuestion = 0;
    gameState = EnumGameState::GAME_RUNNING;

    // Prepare question
    totalQuestion = TOTAL_PLAYER * QUESTION_PER_PLAYER;
    selectedQuestion = pick(questions.size(), totalQuestion);
    for (int i = 0; i < totalQuestion; ++i) {
        questions[selectedQuestion[i]].id = i + 1;
    }

    // Send game info
    int i = 1;
    for (auto &player : players) {
        send(*player->socket, ACTION_GAME_INFO, TOTAL_PLAYER << i++ << totalQuestion);
    }
}

void Game::sendQuestion() {
    if (countAlivePlayer() == 0) {
        LOG_INFO("No player alive");
        gameState = EnumGameState::GAME_FINISHED;
        return;
    }

    // Find alive player
    while (players[currentPlayer] == NULL) {
        currentPlayer = (currentPlayer + 1) % TOTAL_PLAYER;
    }

    // Send question
    send(*players[currentPlayer]->socket, ACTION_QUESTION, questions[selectedQuestion[currentQuestion]]);
    LOG_INFO("Send question " << currentQuestion << " to player " << players[currentPlayer]->name);
}
