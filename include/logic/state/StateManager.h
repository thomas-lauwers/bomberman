#ifndef BOMBERMAN_STATEMANAGER_H
#define BOMBERMAN_STATEMANAGER_H

#include "State.h"
#include <memory>
#include <stack>

namespace sf {
    class RenderWindow;
}

using namespace std;

class StateManager {
public:
    void pushState(unique_ptr<State> state);
    void popState();

    void handleInput();
    void update();
    void render(sf::RenderWindow& window);

private:
    stack<unique_ptr<State>> states{};

};


#endif //BOMBERMAN_STATEMANAGER_H
