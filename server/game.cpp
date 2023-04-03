#include "game.h"

bool Game::isValidName(std::string name) {
    // check if name exist
    for (int i = 0; i < currentPlayer; i++) {
        if (player[i].name == name) return false;
    }
    return std::regex_match(name, std::regex(name_pattern));
}

bool Game::registerPlayer(sf::TcpSocket &client, Player &player) {
    sf::Packet receive_packet;
    perr(client.receive(receive_packet), "Error receiving player registration");

    // Read action
    std::string action;
    receive_packet >> action;
    if (action != "register") {
        std::cout << "Wait for \"register\", receive \"" << action << "\"\n";
        send_result(client, false);
        client.disconnect();
        return 0;
    }

    // Read name
    receive_packet >> player.name;
    if (!isValidName(player.name)) {
        std::cout << "Player name is invalid\n";
        send_result(client, false);
        client.disconnect();
        return 0;
    }

    send_result(client, true);
    return 1;
}

void Game::run() {
    // Open server
    perr(listener.listen(PORT), "Error listening on port " << PORT);

    // Wait for player to register
    while (currentPlayer < TOTAL_PLAYER) {
        perr(listener.accept(client[currentPlayer]), "Error accepting client");

        if (!registerPlayer(client[currentPlayer], player[currentPlayer])) {
            std::cout << "Player " << currentPlayer << " failed to register\n";
            continue;
        }

        currentPlayer++;
    }

    std::cout << "All player registered\n";
    for (int i = 0; i < TOTAL_PLAYER; i++) {
        std::cout << player[i].name << '\n';
    }
}