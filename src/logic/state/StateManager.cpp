#include "../../../include/logic/state/StateManager.h"

void StateManager::pushState(std::unique_ptr<State> state) {
    states.push(std::move(state));
}

void StateManager::popState() {
    if (!states.empty()) {
        states.pop();
    }
}

void StateManager::handleInput() const {
    if (!states.empty()) {
        states.top()->handleInput();
    }
}

void StateManager::update() const {
    if (!states.empty()) {
        states.top()->update();
    }
}

void StateManager::render(sf::RenderWindow& window) const {
    if (!states.empty()) {
        states.top()->render(window);
    }
}