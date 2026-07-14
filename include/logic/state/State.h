#ifndef BOMBERMAN_STATE_H
#define BOMBERMAN_STATE_H

#include "../IWorldView.h"
#include "../Input.h"

namespace sf {
    class RenderWindow;
}

class IWorldView;

class State {
public:
    virtual ~State() = default;

    virtual void handleInput(Input input) {}
    virtual void update(float deltaTime, IWorldView& renderer) = 0;
    virtual void render(sf::RenderWindow& window, IWorldView& renderer) = 0;
};

#endif //BOMBERMAN_STATE_H
