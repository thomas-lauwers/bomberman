/**
 * @file ExplosionView.h
 * @brief Defines the ExplosionView class for rendering explosion entities.
 */

#ifndef BOMBERMAN_EXPLOSIONVIEW_H
#define BOMBERMAN_EXPLOSIONVIEW_H
#include "../../logic/factory/Explosion.h"
#include "../Animation.h"
#include "IEntityView.h"

class TextureManager;

/**
 * @class ExplosionView
 * @brief View component for rendering explosion entities with animation support.
 */
class ExplosionView : public IEntityView {
public:
    /**
     * @brief Constructs an ExplosionView instance.
     * @param t_manager Reference to the texture manager.
     * @param type The type of the explosion (center, horizontal, etc.).
     */
    explicit ExplosionView(const TextureManager& t_manager, ExplosionType type);

    /**
     * @brief Draws the explosion representation on the window.
     * @param window The SFML render window.
     * @param entity The explosion entity model.
     */
    void draw(sf::RenderWindow& window, const Entity& entity) override;
    
    /**
     * @brief Updates the explosion view animation.
     * @param deltaTime Time elapsed since last update.
     */
    void update(float deltaTime) override;
    
    /**
     * @brief Handles notifications about explosion events.
     * @param entity The explosion entity that triggered the event.
     * @param event The event that occurred.
     */
    void onNotify(const Entity& entity, Event event) override;

private:
    sf::Sprite sprite;              ///< The sprite for rendering
    Animation animation;            ///< Animation for the explosion
    ExplosionType type;             ///< The type of explosion
    
    float animationTimer = 0.0f;    ///< Timer for frame switching
    size_t frameIndex = 0;          ///< Current animation frame index
};

#endif // BOMBERMAN_EXPLOSIONVIEW_H
