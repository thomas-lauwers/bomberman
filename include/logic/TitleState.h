#ifndef BOMBERMAN_TITLESTATE_H
#define BOMBERMAN_TITLESTATE_H
#include "State.h"
#include <SFML/Graphics.hpp>

class TitleState : public State {
public:
    void handleInput() override;
    void update() override;
    void render(sf::RenderWindow& window) override;
};


#endif //BOMBERMAN_TITLESTATE_H
