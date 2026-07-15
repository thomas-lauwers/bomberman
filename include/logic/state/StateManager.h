#ifndef BOMBERMAN_STATEMANAGER_H
#define BOMBERMAN_STATEMANAGER_H

#include "State.h"
#include <memory>
#include <stack>

class StateManager {
public:
    void pushState(std::unique_ptr<State> state);
    void popState();

    void update(float deltaTime, IWorldView& renderer) const;
    [[nodiscard]] State* getCurrentState() const;

private:
    std::stack<std::unique_ptr<State>> states{};
};

#endif // BOMBERMAN_STATEMANAGER_H
