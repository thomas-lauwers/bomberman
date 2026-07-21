/**
 * @file Input.h
 * @brief Defines the Input enum for player actions.
 */

#ifndef BOMBERMAN_INPUT_H
#define BOMBERMAN_INPUT_H

/**
 * @enum Input
 * @brief Represents possible player input actions.
 */
enum class Input { 
    MoveLeft,   ///< Move left
    MoveRight,  ///< Move right
    MoveUp,     ///< Move up
    MoveDown,   ///< Move down
    PlaceBomb,  ///< Place a bomb
    Select      ///< Select/Confirm action
};

#endif
