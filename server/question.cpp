#include "question.h"

sf::Packet& operator<<(sf::Packet& packet, const Question& q) {
    return packet << q.title << q.choice_A << q.choice_B << q.choice_C << q.choice_D;
}