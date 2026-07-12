#ifndef BOMBERMAN_PAUSESTATE_H
#define BOMBERMAN_PAUSESTATE_H
#include "State.h"

class PauseState : public State {
public:
    void update() override;
    void render(sf::RenderWindow& window, IWorldView& renderer) override;
};


#endif //BOMBERMAN_PAUSESTATE_H
