/**
 * @file PlayerView.h
 * @brief Defines the PlayerView class for rendering the player entity.
 */

#ifndef BOMBERMAN_PLAYERVIEW_H
#define BOMBERMAN_PLAYERVIEW_H
#include "BomberView.h"

/**
 * @class PlayerView
 * @brief View component for rendering the player-controlled bomber entity.
 */
class PlayerView : public BomberView {
public:
    /**
     * @brief Constructs a PlayerView instance.
     * @param t_manager Reference to the texture manager.
     */
    explicit PlayerView(const TextureManager& t_manager);
    
    /**
     * @brief Draws the player representation on the window.
     * @param window The SFML render window.
     * @param entity The player entity model.
     */
    void draw(sf::RenderWindow& window, const Entity& entity) override;
};

#endif // BOMBERMAN_PLAYERVIEW_H
