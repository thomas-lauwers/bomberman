/**
 * @file Animation.h
 * @brief Defines the Animation struct for managing entity animations.
 */

#ifndef BOMBERMAN_ANIMATION_H
#define BOMBERMAN_ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @struct Animation
 * @brief Represents an animation sequence.
 */
struct Animation {
    std::vector<sf::IntRect> frames; ///< List of frames in the animation
    float duration;                  ///< Duration of the animation
    bool loop;                       ///< Whether the animation loops
};

#endif // BOMBERMAN_ANIMATION_H
