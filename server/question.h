#ifndef QUESTION_H
#define QUESTION_H

#include <SFML/Network.hpp>
#include <fstream>
#include <string>

struct Question {
    std::string title, explanation;
    std::string choice_A, choice_B, choice_C, choice_D;
    char correct;

    friend sf::Packet& operator<<(sf::Packet& packet, const Question& q);
    friend std::ifstream& operator>>(std::ifstream& file, Question& q);
};

#endif  // QUESTION_H