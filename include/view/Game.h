#ifndef BOMBERMAN_GAME_H
#define BOMBERMAN_GAME_H

#include "../logic/StateManager.h"
#include <SFML/Graphics.hpp>
#include <memory>
using namespace std;

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    unique_ptr<StateManager> state_manager;
};


#endif //BOMBERMAN_GAME_H
