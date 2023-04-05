#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "constant.h"
#include "logger.h"
#include "question.h"
#include "screen.h"

typedef struct {
    int code;
    std::string message;
} Response;

class Player {
private:
    sf::TcpSocket socket;
    sf::SocketSelector selector;

public:
    bool can_skip;  // can skip the question only once

    Player();

    void handle_socket();

    void send_register_request(std::string name);
    void send_answer(std::string answer);
    void send_skip_request();

    Response receive_register_response();
    void receive_game_info();
    Question receive_question();
    Response receive_answer_response();
};

extern Player player;

extern int num_players;
extern int player_id;
extern int num_questions;

extern int wait_event;

#endif  // _PLAYER_H_
