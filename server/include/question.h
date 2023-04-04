#ifndef QUESTION_H
#define QUESTION_H

#include <SFML/Network.hpp>
#include <fstream>
#include <sstream>
#include <string>

struct Question {
    Question() {}
    Question(std::string line);

    std::string title;
    std::string choice_A, choice_B, choice_C, choice_D;
    char correct;

    friend sf::Packet& operator<<(sf::Packet& packet, const Question& q);
};

#endif  // QUESTION_H