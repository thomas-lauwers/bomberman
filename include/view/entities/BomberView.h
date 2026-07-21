/**
 * @file BomberView.h
 * @brief Defines the BomberView class for rendering bomber entities.
 */

#ifndef BOMBERMAN_BOMBERVIEW_H
#define BOMBERMAN_BOMBERVIEW_H
#include "../AnimationState.h"
#include "../BomberAnimationConfig.h"
#include "../Direction.h"
#include "IEntityView.h"
#include <SFML/Graphics.hpp>

class TextureManager;

/**
 * @class BomberView
 * @brief Base class for rendering bomber entities with animation support.
 */
class BomberView : public IEntityView {
public:
    /**
     * @brief Constructs a BomberView instance.
     * @param t_manager Reference to the texture manager.
     */
    explicit BomberView(const TextureManager& t_manager);

    /**
     * @brief Destructor for BomberView.
     */
    ~BomberView() override = default;

    /**
     * @brief Draws the bomber representation on the window.
     * @param window The SFML render window.
     * @param entity The bomber entity model.
     */
    void draw(sf::RenderWindow& window, const Entity& entity) override;

    /**
     * @brief Updates the bomber view animation.
     * @param deltaTime Time elapsed since last update.
     */
    void update(float deltaTime) override;

    /**
     * @brief Handles notifications about bomber events.
     * @param entity The bomber entity that triggered the event.
     * @param event The event that occurred.
     */
    void onNotify(const Entity& entity, Event event) override;

protected:
    /**
     * @brief Sets up animations for the bomber.
     * @param xOffset X offset in the sprite sheet.
     * @param yOffset Y offset in the sprite sheet.
     */
    void setupAnimations(int xOffset, int yOffset);

    sf::Sprite sprite;                     ///< The sprite for rendering
    BomberAnimationConfig animationConfig; ///< Configuration for bomber animations

    AnimationState currentAction; ///< The current animation action
    Direction currentDirection;   ///< The current facing direction

    float animationTimer = 0.0f; ///< Timer for frame switching
    size_t frameIndex = 0;       ///< Current animation frame index
};

#endif // BOMBERMAN_BOMBERVIEW_H
