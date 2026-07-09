#ifndef BOMBERMAN_PLAYSTATE_H
#define BOMBERMAN_PLAYSTATE_H
#include "State.h"
#include <SFML/Graphics.hpp>

class PlayState : public State {
public:
    void handleInput() override;
    void update() override;
    void render(sf::RenderWindow& window) override;
};


#endif //BOMBERMAN_PLAYSTATE_H
