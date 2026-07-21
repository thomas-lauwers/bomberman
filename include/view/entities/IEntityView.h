/**
 * @file IEntityView.h
 * @brief Defines the IEntityView interface for entity representation in the view layer.
 */

#ifndef BOMBERMAN_IENTITYVIEW_H
#define BOMBERMAN_IENTITYVIEW_H

#include "../../logic/Observer.h"
#include <SFML/Graphics.hpp>

class Entity;

/**
 * @class IEntityView
 * @brief Interface for view components representing game entities.
 * Inherits from Observer to listen for entity events.
 */
class IEntityView : public Observer {
public:
    /**
     * @brief Destructor for IEntityView.
     */
    ~IEntityView() override = default;

    /**
     * @brief Draws the entity representation on the window.
     * @param window The SFML render window.
     * @param entity The entity model.
     */
    virtual void draw(sf::RenderWindow& window, const Entity& entity) = 0;

    /**
     * @brief Updates the entity view animation/timing.
     * @param deltaTime Time elapsed since last update.
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Handles notifications about entity events.
     * @param entity The entity that triggered the event.
     * @param event The event that occurred.
     */
    void onNotify(const Entity& entity, Event event) override = 0;
};

#endif // BOMBERMAN_IENTITYVIEW_H
