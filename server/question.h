#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <SFML/Network.hpp>

struct Question {
    std::string title;
    std::string choice_A, choice_B, choice_C, choice_D;

    friend sf::Packet& operator <<(sf::Packet& packet, const Question& q);
};


#endif // QUESTION_H