#include "../../../include/logic/state/StateManager.h"

void StateManager::pushState(std::unique_ptr<State> state) { states.push(std::move(state)); }

void StateManager::popState() {
    if (!states.empty()) {
        states.pop();
    }
}

void StateManager::update(const float deltaTime, IWorldView& renderer) const {
    if (!states.empty()) {
        states.top()->update(deltaTime, renderer);
    }
}

State* StateManager::getCurrentState() const {
    if (!states.empty()) {
        return states.top().get();
    }
    return nullptr;
}