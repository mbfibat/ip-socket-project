#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <SFML/Network.hpp>
#include <iostream>
#include <string>

struct GameInfo {
public:
    int num_players;
    int num_questions;
    int time_per_question;

    friend std::ostream& operator<<(std::ostream& out, const GameInfo& info);
    friend sf::Packet& operator>>(sf::Packet& packet, GameInfo& info);
};

#endif  // GAMEINFO_H