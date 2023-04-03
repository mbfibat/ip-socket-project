#include "question.h"

std::ostream& operator<<(std::ostream& out, const Question& q) {
    out << q.title << std::endl;
    out << "A. " << q.choice_A << std::endl;
    out << "B. " << q.choice_B << std::endl;
    out << "C. " << q.choice_C << std::endl;
    out << "D. " << q.choice_D << std::endl;
    return out;
}

sf::Packet& operator>>(sf::Packet& packet, Question& q) {
    return packet >> q.title >> q.choice_A >> q.choice_B >> q.choice_C >>
           q.choice_D;
}