#ifndef CONSTANT_H
#define CONSTANT_H

#define IP "127.0.0.1"
#define PORT 5000
#define DATA_FOLDER "data/"
#define TOTAL_PLAYER 3
#define QUESTION_PER_PLAYER 5

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

#define name_pattern "[a-zA-Z0-9_]{1,10}"

#endif  // CONSTANT_H