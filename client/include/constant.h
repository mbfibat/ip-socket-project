#ifndef CONSTANT_H
#define CONSTANT_H

#include <string>

const static int WIDTH = 1440;
const static int HEIGHT = 900;
const static int PORT = 5000;
const static std::string IP = "127.0.0.1";

#define DELAY_MS 100

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