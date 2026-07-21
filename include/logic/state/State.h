/**
 * @file State.h
 * @brief Defines the base State interface for the game state machine.
 */

#ifndef BOMBERMAN_STATE_H
#define BOMBERMAN_STATE_H

#include "../IWorldView.h"
#include "../Input.h"

class IWorldView;

/**
 * @class State
 * @brief Base class for all game states.
 */
class State {
public:
    virtual ~State() = default;

    /**
     * @brief Handles user input for this state.
     * @param input The input action.
     */
    virtual void handleInput(Input input) {}

    /**
     * @brief Updates the logic for this state.
     * @param deltaTime The time elapsed since the last update.
     * @param renderer The world renderer interface.
     */
    virtual void update(float deltaTime, IWorldView& renderer) = 0;

    /**
     * @brief Renders the state.
     * @param renderer The world renderer interface.
     */
    virtual void render(IWorldView& renderer) = 0;
};

#endif // BOMBERMAN_STATE_H
