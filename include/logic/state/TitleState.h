#ifndef BOMBERMAN_TITLESTATE_H
#define BOMBERMAN_TITLESTATE_H
#include "State.h"

class TitleState : public State {
public:
    void update() override;
    void render(sf::RenderWindow& window) override;
};


#endif //BOMBERMAN_TITLESTATE_H
