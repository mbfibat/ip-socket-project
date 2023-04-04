#include "../include/game.h"

int main() {
    Game game;
    while (true) {
        game.init();
        game.run();
    }
}