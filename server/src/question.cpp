#include "../include/question.h"

Question::Question(std::string line) {
    std::stringstream ss(line);
    std::string token;
    std::getline(ss, token, ',');
    title = token;
    std::getline(ss, token, ',');
    choice_A = token;
    std::getline(ss, token, ',');
    choice_B = token;
    std::getline(ss, token, ',');
    choice_C = token;
    std::getline(ss, token, ',');
    choice_D = token;
    std::getline(ss, token, ',');
    correct = token[0];
}

sf::Packet& operator<<(sf::Packet& packet, const Question& q) {
    return packet << q.title << q.choice_A << q.choice_B << q.choice_C << q.choice_D;
}