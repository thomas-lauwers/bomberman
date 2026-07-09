#include "../../../include/logic/state/StateManager.h"

void StateManager::pushState(unique_ptr<State> state) {
    states.push(std::move(state));
}

void StateManager::popState() {
    if (!states.empty()) {
        states.pop();
    }
}

void StateManager::handleInput() {
    if (!states.empty()) {
        states.top()->handleInput();
    }
}

void StateManager::update() {
    if (!states.empty()) {
        states.top()->update();
    }
}

void StateManager::render(sf::RenderWindow& window) {
    if (!states.empty()) {
        states.top()->render(window);
    }
}