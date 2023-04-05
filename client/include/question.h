#ifndef QUESTION_H
#define QUESTION_H

#include <iostream>
#include <string>

#include "socket.h"

struct Question {
public:
    int id;
    std::string title;
    std::string choice_A, choice_B, choice_C, choice_D;

    friend std::ostream& operator<<(std::ostream& out, const Question& q);
    friend sf::Packet& operator>>(sf::Packet& packet, Question& q);
};

#endif  // QUESTION_H