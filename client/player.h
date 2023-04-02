/*
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "packet.h"

class Player {
public:
    sf::TcpSocket socket;

    bool register_account(char* name);
    void receive_game_info();
    Question receive_question();
};
#endif
*/