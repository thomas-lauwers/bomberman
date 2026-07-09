#ifndef BOMBERMAN_STATE_H
#define BOMBERMAN_STATE_H

namespace sf {
    class RenderWindow;
}

class State {
public:
    virtual ~State() = default;

    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};

#endif //BOMBERMAN_STATE_H
