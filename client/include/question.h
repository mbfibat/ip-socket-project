#ifndef QUESTION_H
#define QUESTION_H

#include <SFML/Network.hpp>
#include <iostream>
#include <string>

struct Question {
public:
    std::string title;
    std::string choice_A, choice_B, choice_C, choice_D;

    friend std::ostream& operator<<(std::ostream& out, const Question& q);

    friend sf::Packet& operator>>(sf::Packet& packet, Question& q);
};

#endif  // QUESTION_H