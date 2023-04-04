#ifndef CONSTANT_H
#define CONSTANT_H

// Configurations

#define IP "127.0.0.1"
#define PORT 5000
#define WIDTH 900
#define HEIGHT 600
#define BACKGROUND_IMG_PATH "assets/image/background.png"
#define FONT_PATH "assets/fonts/Montserrat-Regular.ttf"

#define DELAY_MS 100
#define TIMER_SEC 30

// Constants

#define ACTION_REGISTER "register"
#define ACTION_ANSWER "answer"
#define ACTION_SKIP "skip"
#define ACTION_EXIT "exit"

#define CODE_ERROR -1
#define CODE_SUCCESS 0
#define CODE_WIN 1
#define CODE_LOSE 2
#define CODE_CORRECT 3
#define CODE_WRONG_TURN 4
#define CODE_ALREADY_SKIP 5

#endif  // CONSTANT_H