/**
 * @file IWorldView.h
 * @brief Defines the IWorldView interface for rendering the game world.
 */

#ifndef BOMBERMAN_IWORLDVIEW_H
#define BOMBERMAN_IWORLDVIEW_H
#include <string>

class World;

/**
 * @class IWorldView
 * @brief Interface for rendering the game world and UI elements.
 */
class IWorldView {
public:
    virtual ~IWorldView() = default;

    /**
     * @brief Renders the game world.
     * @param world The game world to render.
     */
    virtual void render(const World& world) = 0;

    /**
     * @brief Updates rendering-related logic (e.g., animations).
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Renders text centered on the screen.
     * @param text The text to render.
     * @param y The vertical position of the text.
     */
    virtual void renderCenteredText(const std::string& text, float y) = 0;

    /**
     * @brief Renders text at a specific position.
     * @param text The text to render.
     * @param x The x coordinate.
     * @param y The y coordinate.
     */
    virtual void renderText(const std::string& text, float x, float y) = 0;

    /**
     * @brief Renders the bomberman portrait.
     * @param x The x coordinate.
     * @param y The y coordinate.
     */
    virtual void renderPortrait(float x, float y) = 0;

    /**
     * @brief Renders the title screen.
     * @param showEnter Whether to show the "Press ENTER" text.
     */
    virtual void renderTitle(bool showEnter) = 0;
};

#endif // BOMBERMAN_IWORLDVIEW_H
