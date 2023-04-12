#ifndef CONSTANT_H
#define CONSTANT_H

// Configurations

#define IP "127.0.0.1"
#define PORT 5000
#define DATA_FOLDER "data/"
#define QUESTION_PER_PLAYER 5
#define DELAY_MS 100

// Constants

#define name_pattern "[a-zA-Z0-9_]{1,10}"

enum EnumGameState {
    WAITING_FOR_PLAYER = 0,
    GAME_RUNNING = 1,
    GAME_FINISHED = 2
};

#endif  // CONSTANT_H
