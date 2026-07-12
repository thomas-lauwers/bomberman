#ifndef BOMBERMAN_PAUSESTATE_H
#define BOMBERMAN_PAUSESTATE_H
#include "State.h"
#include <SFML/Graphics.hpp>

class PauseState : public State {
public:
    void update() override;
    void render(sf::RenderWindow& window) override;
};


#endif //BOMBERMAN_PAUSESTATE_H
