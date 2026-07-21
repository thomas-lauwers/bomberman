/**
 * @file TitleState.h
 * @brief Defines the TitleState class for the title screen.
 */

#ifndef BOMBERMAN_TITLESTATE_H
#define BOMBERMAN_TITLESTATE_H
#include "../Score.h"
#include "State.h"
#include <functional>

/**
 * @class TitleState
 * @brief Represents the title screen state.
 */
class TitleState : public State {
public:
    /**
     * @brief Constructs a new TitleState instance.
     * @param onSelect Callback function triggered when a selection is made.
     */
    explicit TitleState(std::function<void()> onSelect);
    ~TitleState() override;

    /**
     * @brief Handles user input for the title screen.
     * @param input The input action.
     */
    void handleInput(Input input) override;

    /**
     * @brief Updates the logic for the title screen.
     * @param deltaTime The time elapsed since the last update.
     * @param renderer The world renderer interface.
     */
    void update(float deltaTime, IWorldView& renderer) override;

    /**
     * @brief Renders the title screen.
     * @param renderer The world renderer interface.
     */
    void render(IWorldView& renderer) override;

private:
    float blinkTimer = 0.0f;        ///< Timer for text blinking effect
    bool showText = true;           ///< Flag to control text visibility
    std::function<void()> onSelect; ///< Callback for selection
    Score score;                    ///< Score instance for displaying high scores
};

#endif // BOMBERMAN_TITLESTATE_H
