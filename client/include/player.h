#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "constant.h"
#include "logger.h"
#include "question.h"

typedef struct {
    int code;
    std::string message;
} Response;

class Player {
public:
    Player();

    Response register_account(std::string name);
    void receive_game_info();
    Question receive_question();
    Response send_answer(std::string answer);
    Response skip_question();

    sf::TcpSocket socket;
    bool can_skip;  // can skip the question only once
};

extern Player player;
extern int num_players;
extern int player_id;
extern int num_questions;

#endif
