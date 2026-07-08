#include "representation/StateManager.h"

namespace rep {

StateManager::StateManager() : currentState(GameState::Gameplay) {}

void StateManager::setState(GameState newState) {
    currentState = newState;
}

GameState StateManager::getState() const {
    return currentState;
}

} // namespace rep
