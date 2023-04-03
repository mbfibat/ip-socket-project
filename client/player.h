
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "gameinfo.h"
#include "question.h"

class Player {
public:
    sf::TcpSocket socket;
    sf::SocketSelector selector;

    bool can_skip;  // can skip the question only once

    Player();
    void receive_game_info();
    Question receive_question();

    void skip_question();
    void send_answer(std::string answer);

    bool register_account(std::string name);

    void test();
};

#endif
