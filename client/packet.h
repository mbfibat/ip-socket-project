#ifndef _PACKET_H_
#define _PACKET_H_

#include <string>
#include <iostream>
#include <SFML/Network.hpp>

struct Question {
public:
    std::string title;
    std::string choice_A, choice_B, choice_C, choice_D;

    friend std::ostream& operator <<(std::ostream& out, const Question& q) {
            out << q.title << std::endl;
            out << "A. " << q.choice_A << std::endl;
            out << "B. " << q.choice_B << std::endl;
            out << "C. " << q.choice_C << std::endl;
            out << "D. " << q.choice_D << std::endl;
            return out;
    }
    friend sf::Packet& operator >>(sf::Packet& packet, Question& q) {
        return packet >> q.title >> q.choice_A >> q.choice_B >> q.choice_C >> q.choice_D;
    }
};


struct GameInfo {
public:
    int num_players;
    int num_questions;
    int time_per_question;

    friend std::ostream& operator <<(std::ostream& out, const GameInfo& info);
    friend sf::Packet& operator >>(sf::Packet& packet, GameInfo& info);
};

#endif