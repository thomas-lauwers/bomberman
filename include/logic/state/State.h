#ifndef BOMBERMAN_STATE_H
#define BOMBERMAN_STATE_H

#include "../Input.h"

namespace sf {
    class RenderWindow;
}

class State {
public:
    virtual ~State() = default;

    virtual void handleInput(Input input) {}
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};

#endif //BOMBERMAN_STATE_H
