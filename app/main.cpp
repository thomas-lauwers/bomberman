#include "bomberman/Game.hpp"

#include <iostream>

int main() {
    bomberman::Game game;
    game.update();
    std::cout << "Bomberman core initialized. Current score: " << game.score().current() << '\n';
    return 0;
}
