
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "gameinfo.h"
#include "question.h"

class Player {
public:
    sf::TcpSocket socket;

    Player();
    void receive_game_info();
    Question receive_question();
    bool register_account(std::string& name);

    void test();
};
#endif
