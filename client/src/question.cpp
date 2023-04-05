#include "../include/question.h"

std::ostream& operator<<(std::ostream& out, const Question& q) {
    out << q.id << '\n';
    out << q.title << '\n';
    out << "A. " << q.choice_A << '\n';
    out << "B. " << q.choice_B << '\n';
    out << "C. " << q.choice_C << '\n';
    out << "D. " << q.choice_D << '\n';
    return out;
}

sf::Packet& operator>>(sf::Packet& packet, Question& q) {
    return packet >> q.id >> q.title >> q.choice_A >> q.choice_B >> q.choice_C >> q.choice_D;
}