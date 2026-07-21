/**
 * @file DestructibleWallView.h
 * @brief Defines the DestructibleWallView class for rendering destructible wall entities.
 */

#ifndef BOMBERMAN_DESTRUCTIBLEWALLVIEW_H
#define BOMBERMAN_DESTRUCTIBLEWALLVIEW_H
#include "IEntityView.h"

class TextureManager;

/**
 * @class DestructibleWallView
 * @brief View component for rendering destructible wall entities.
 */
class DestructibleWallView : public IEntityView {
public:
    /**
     * @brief Constructs a DestructibleWallView instance.
     * @param t_manager Reference to the texture manager.
     */
    explicit DestructibleWallView(const TextureManager& t_manager);

    /**
     * @brief Draws the destructible wall representation on the window.
     * @param window The SFML render window.
     * @param entity The destructible wall entity model.
     */
    void draw(sf::RenderWindow& window, const Entity& entity) override;
    
    /**
     * @brief Updates the destructible wall view (no animation needed for static wall).
     * @param deltaTime Time elapsed since last update.
     */
    void update(float deltaTime) override;
    
    /**
     * @brief Handles notifications about destructible wall events.
     * @param entity The destructible wall entity that triggered the event.
     * @param event The event that occurred.
     */
    void onNotify(const Entity& entity, Event event) override;

private:
    sf::Sprite sprite; ///< The sprite for rendering
};

#endif // BOMBERMAN_DESTRUCTIBLEWALLVIEW_H
