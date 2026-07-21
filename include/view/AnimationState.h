/**
 * @file AnimationState.h
 * @brief Defines the AnimationState enum for character animation actions.
 */

#ifndef BOMBERMAN_ANIMATIONSTATE_H
#define BOMBERMAN_ANIMATIONSTATE_H

/**
 * @enum AnimationState
 * @brief Represents the possible action states for character animations.
 */
enum class AnimationState {
    Idle,   ///< Character is idle
    Moving, ///< Character is moving
};

#endif // BOMBERMAN_ANIMATIONSTATE_H
