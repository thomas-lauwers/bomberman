#ifndef BOMBERMAN_TITLESTATE_H
#define BOMBERMAN_TITLESTATE_H
#include "State.h"

class TitleState : public State {
public:
    void update(float deltaTime, IWorldView& renderer) override;
    void render(sf::RenderWindow& window, IWorldView& renderer) override;
};


#endif //BOMBERMAN_TITLESTATE_H
