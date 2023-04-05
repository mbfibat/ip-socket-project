#ifndef SOCKET_H
#define SOCKET_H

#include <SFML/Network.hpp>

// Client -> Server
#define ACTION_REGISTER 40  // send{player_name}, receive{code, msg} (code = ERROR|SUCCESS)
#define ACTION_ANSWER 41    // send{player_name, question_id, answer}, receive{code, msg} (code = ERROR|CORRECT|WIN|LOSE)
#define ACTION_SKIP 42      // send{player_name, question_id}, receive{code, msg} (code = ERROR|SUCCESS)
#define ACTION_EXIT 43      // send{player_name}, receive{code, msg} (code = ERROR|SUCCESS)
#define ACTION_NONE 44

// Server -> Client
#define ACTION_GAME_INFO 44  // send{total_player, player_id, total_question}
#define ACTION_QUESTION 45   // send{question_id, question, answer_a, answer_b, answer_c, answer_d}

#define CODE_ERROR -1
#define CODE_SUCCESS 0
#define CODE_WIN 1
#define CODE_LOSE 2
#define CODE_CORRECT 3

#define send(client, action, data)                  \
    {                                               \
        sf::Packet p;                               \
        p << action << data;                        \
        if ((client).send(p) != sf::Socket::Done) { \
            LOG_ERROR("Error sending packet");      \
        }                                           \
    }

#endif  // SOCKET_H