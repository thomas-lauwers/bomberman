/**
 * @file KnockedOutBomberView.h
 * @brief Defines the KnockedOutBomberView class for rendering knocked-out bomber entities.
 */

#ifndef BOMBERMAN_KNOCKEDOUTBOMBERVIEW_H
#define BOMBERMAN_KNOCKEDOUTBOMBERVIEW_H
#include "../../logic/factory/BomberType.h"
#include "../Animation.h"
#include "IEntityView.h"

class TextureManager;

/**
 * @class KnockedOutBomberView
 * @brief View component for rendering knocked-out bomber entities with animation support.
 */
class KnockedOutBomberView : public IEntityView {
public:
    /**
     * @brief Constructs a KnockedOutBomberView instance.
     * @param t_manager Reference to the texture manager.
     * @param type The type of the bomber.
     */
    explicit KnockedOutBomberView(const TextureManager& t_manager, BomberType type);

    /**
     * @brief Draws the knocked-out bomber representation on the window.
     * @param window The SFML render window.
     * @param entity The knocked-out bomber entity model.
     */
    void draw(sf::RenderWindow& window, const Entity& entity) override;
    
    /**
     * @brief Updates the knocked-out bomber view animation.
     * @param deltaTime Time elapsed since last update.
     */
    void update(float deltaTime) override;
    
    /**
     * @brief Handles notifications about knocked-out bomber events.
     * @param entity The knocked-out bomber entity that triggered the event.
     * @param event The event that occurred.
     */
    void onNotify(const Entity& entity, Event event) override;

private:
    sf::Sprite sprite;              ///< The sprite for rendering
    BomberType type;                ///< The type of the bomber
    Animation animation;            ///< Animation for the knocked-out bomber
    float animationTimer = 0.0f;    ///< Timer for frame switching
    size_t frameIndex = 0;          ///< Current animation frame index

    float bounceTimer = 0.0f;       ///< Timer for the bouncing effect
    float bounceDuration = 0.3f;    ///< Duration of the bounce animation
    float bounceAmplitude = 2.0f;   ///< Amplitude of the bounce effect
};

#endif // BOMBERMAN_KNOCKEDOUTBOMBERVIEW_H
