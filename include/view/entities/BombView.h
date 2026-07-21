/**
 * @file BombView.h
 * @brief Defines the BombView class for rendering bomb entities.
 */

#ifndef BOMBERMAN_BOMBVIEW_H
#define BOMBERMAN_BOMBVIEW_H
#include "../Animation.h"
#include "IEntityView.h"

class TextureManager;

/**
 * @class BombView
 * @brief View component for rendering bomb entities with animation support.
 */
class BombView : public IEntityView {
public:
    /**
     * @brief Constructs a BombView instance.
     * @param t_manager Reference to the texture manager.
     */
    explicit BombView(const TextureManager& t_manager);

    /**
     * @brief Draws the bomb representation on the window.
     * @param window The SFML render window.
     * @param entity The bomb entity model.
     */
    void draw(sf::RenderWindow& window, const Entity& entity) override;
    
    /**
     * @brief Updates the bomb view animation.
     * @param deltaTime Time elapsed since last update.
     */
    void update(float deltaTime) override;
    
    /**
     * @brief Handles notifications about bomb events.
     * @param entity The bomb entity that triggered the event.
     * @param event The event that occurred.
     */
    void onNotify(const Entity& entity, Event event) override;

private:
    sf::Sprite sprite;                      ///< The sprite for rendering
    Animation animation;                    ///< Animation for the bomb
    float animationTimer = 0.0f;            ///< Timer for frame switching
    size_t frameIndex = 0;                  ///< Current animation frame index
};

#endif // BOMBERMAN_BOMBVIEW_H
