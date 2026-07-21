/**
 * @file StateManager.h
 * @brief Defines the StateManager class for managing the game state stack.
 */

#ifndef BOMBERMAN_STATEMANAGER_H
#define BOMBERMAN_STATEMANAGER_H

#include "State.h"
#include <memory>
#include <stack>

/**
 * @class StateManager
 * @brief Manages the stack of game states.
 */
class StateManager {
public:
    /**
     * @brief Pushes a new state onto the stack.
     * @param state Unique pointer to the state.
     */
    void pushState(std::unique_ptr<State> state);

    /**
     * @brief Pops the top state from the stack.
     */
    void popState();

    /**
     * @brief Updates the current state.
     * @param deltaTime Time elapsed since last update.
     * @param renderer The world renderer interface.
     */
    void update(float deltaTime, IWorldView& renderer) const;

    /**
     * @brief Gets the current top state.
     * @return Pointer to the current state.
     */
    [[nodiscard]] State* getCurrentState() const;

private:
    std::stack<std::unique_ptr<State>> states{}; ///< Stack of game states
};

#endif // BOMBERMAN_STATEMANAGER_H
