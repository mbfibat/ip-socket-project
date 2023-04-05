#include "../include/question.h"

std::istream& operator>>(std::istream& is, Question& q) {
    std::string line, token;
    std::getline(is, line);
    std::stringstream ss(line);

    int len = 0;
    std::vector<std::string> tokens;
    for (int i = 0; i < 6; i++) {
        std::getline(ss, token, ',');
        if (token.size() < 3) {
            break;
        }
        token = token.substr(1, token.size() - 2);
        tokens.push_back(token);

        len += token.size();
    }

    // checksum
    if (len + 17 == line.size()) {
        q.title = tokens[0];
        q.choice_A = tokens[1];
        q.choice_B = tokens[2];
        q.choice_C = tokens[3];
        q.choice_D = tokens[4];
        q.answer = tokens[5];
    }

    return is;
}

sf::Packet& operator<<(sf::Packet& packet, const Question& q) {
    return packet << q.id << q.title << q.choice_A << q.choice_B << q.choice_C << q.choice_D;
}