#ifndef BOMBERMAN_GAME_H
#define BOMBERMAN_GAME_H
#include <SFML/Graphics.hpp>


class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
};


#endif //BOMBERMAN_GAME_H
