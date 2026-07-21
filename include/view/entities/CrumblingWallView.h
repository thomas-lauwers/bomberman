/**
 * @file CrumblingWallView.h
 * @brief Defines the CrumblingWallView class for rendering crumbling wall entities.
 */

#ifndef BOMBERMAN_CRUMBLINGWALLVIEW_H
#define BOMBERMAN_CRUMBLINGWALLVIEW_H
#include "../Animation.h"
#include "IEntityView.h"

class TextureManager;

/**
 * @class CrumblingWallView
 * @brief View component for rendering crumbling wall entities with animation support.
 */
class CrumblingWallView : public IEntityView {
public:
    /**
     * @brief Constructs a CrumblingWallView instance.
     * @param t_manager Reference to the texture manager.
     */
    explicit CrumblingWallView(const TextureManager& t_manager);

    /**
     * @brief Draws the crumbling wall representation on the window.
     * @param window The SFML render window.
     * @param entity The crumbling wall entity model.
     */
    void draw(sf::RenderWindow& window, const Entity& entity) override;

    /**
     * @brief Updates the crumbling wall view animation.
     * @param deltaTime Time elapsed since last update.
     */
    void update(float deltaTime) override;

    /**
     * @brief Handles notifications about crumbling wall events.
     * @param entity The crumbling wall entity that triggered the event.
     * @param event The event that occurred.
     */
    void onNotify(const Entity& entity, Event event) override;

private:
    sf::Sprite sprite;           ///< The sprite for rendering
    Animation animation;         ///< Animation for the crumbling wall
    float animationTimer = 0.0f; ///< Timer for frame switching
    size_t frameIndex = 0;       ///< Current animation frame index
};

#endif // BOMBERMAN_CRUMBLINGWALLVIEW_H