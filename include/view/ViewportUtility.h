/**
 * @file ViewportUtility.h
 * @brief Provides utility functions for managing viewports in the game.
 */

#ifndef BOMBERMAN_VIEWPORT_UTILITY_H
#define BOMBERMAN_VIEWPORT_UTILITY_H

#include <SFML/Graphics.hpp>

/**
 * @class ViewportUtility
 * @brief Utility class for handling game window viewport settings and aspect ratio.
 */
class ViewportUtility {
public:
    /**
     * @brief Sets the viewport for the given window based on the desired content aspect ratio.
     * @param window The render window to update.
     * @param contentAspect The desired aspect ratio of the content.
     */
    static void setViewport(sf::RenderWindow& window, float contentAspect);
};

#endif // BOMBERMAN_VIEWPORT_UTILITY_H
