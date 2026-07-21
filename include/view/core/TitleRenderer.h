/**
 * @file TitleRenderer.h
 * @brief Defines the TitleRenderer class for rendering the title screen layout.
 */

#ifndef BOMBERMAN_TITLERENDERER_H
#define BOMBERMAN_TITLERENDERER_H

#include "../../logic/IWorldView.h"

/**
 * @class TitleRenderer
 * @brief Utility class that encapsulates the rendering logic for the game's title screen.
 */
class TitleRenderer {
public:
    /**
     * @brief Renders the title screen using the provided IWorldView interface.
     * @param renderer The IWorldView implementation used for rendering.
     * @param showEnter Whether to show the blinking "Press Z to Start" text.
     */
    static void render(IWorldView& renderer, bool showEnter);
};

#endif // BOMBERMAN_TITLERENDERER_H
