#include "../../include/logic/StateManager.h"

void StateManager::pushState(unique_ptr<State> state) {
    states.push(std::move(state));
}
void StateManager::popState() {
    states.pop();

}