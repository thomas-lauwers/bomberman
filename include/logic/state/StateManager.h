#ifndef BOMBERMAN_STATEMANAGER_H
#define BOMBERMAN_STATEMANAGER_H

#include "State.h"
#include <memory>
#include <stack>

namespace sf {
    class RenderWindow;
}

class StateManager {
public:
    void pushState(std::unique_ptr<State> state);
    void popState();

    void handleInput() const;
    void update() const;
    void render(sf::RenderWindow& window) const;

private:
    std::stack<std::unique_ptr<State>> states{};

};


#endif //BOMBERMAN_STATEMANAGER_H
