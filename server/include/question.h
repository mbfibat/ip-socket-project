#ifndef QUESTION_H
#define QUESTION_H

#include <fstream>
#include <sstream>
#include <string>

#include "socket.h"

struct Question {
    int id;
    std::string title, answer;
    std::string choice_A, choice_B, choice_C, choice_D;

    friend std::istream& operator>>(std::istream& is, Question& q);
    friend sf::Packet& operator<<(sf::Packet& packet, const Question& q);
};

#endif  // QUESTION_H