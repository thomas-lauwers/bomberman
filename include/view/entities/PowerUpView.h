/**
 * @file PowerUpView.h
 * @brief Defines the PowerUpView class for rendering collectable power-up entities.
 */

#ifndef BOMBERMAN_POWERUPVIEW_H
#define BOMBERMAN_POWERUPVIEW_H
#include "../../logic/factory/PowerUp.h"
#include "../Animation.h"
#include "IEntityView.h"

class TextureManager;

/**
 * @class PowerUpView
 * @brief View component for rendering power-up entities with animation support.
 */
class PowerUpView : public IEntityView {
public:
    /**
     * @brief Constructs a PowerUpView instance.
     * @param t_manager Reference to the texture manager.
     * @param type The type of the power-up.
     */
    explicit PowerUpView(const TextureManager& t_manager, PowerUpType type);

    /**
     * @brief Draws the power-up representation on the window.
     * @param window The SFML render window.
     * @param entity The power-up entity model.
     */
    void draw(sf::RenderWindow& window, const Entity& entity) override;

    /**
     * @brief Updates the power-up view animation.
     * @param deltaTime Time elapsed since last update.
     */
    void update(float deltaTime) override;

    /**
     * @brief Handles notifications about power-up events.
     * @param entity The power-up entity that triggered the event.
     * @param event The event that occurred.
     */
    void onNotify(const Entity& entity, Event event) override;

private:
    sf::Sprite sprite;           ///< The sprite for rendering
    Animation animation;         ///< Animation for the power-up
    PowerUpType type;            ///< The type of the power-up
    float animationTimer = 0.0f; ///< Timer for frame switching
    size_t frameIndex = 0;       ///< Current animation frame index
};

#endif // BOMBERMAN_POWERUPVIEW_H
