#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "constant.h"
#include "main.h"
#include "question.h"

#define LOG(tag, x) std::cerr << tag << '\t' << x << '\n'

class Player {
public:
    sf::TcpSocket socket;

    Player();

    bool can_skip;  // can skip the question only once

    bool connect();
    void receive_game_info();
    Question receive_question();

    void skip_question();
    void send_answer(std::string answer);
    std::string receive_answer_result();
    bool register_account(std::string name);

    void test();
};

extern Player p;

#endif
