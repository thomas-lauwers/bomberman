/**
 * @file Entity.h
 * @brief Defines the base class for all game entities and the EntityType enum.
 */

#ifndef BOMBERMAN_COLLIDABLE_H
#define BOMBERMAN_COLLIDABLE_H
#include "../../utils/Position.h"
#include "../Rect.h"
#include "../Subject.h"

/**
 * @enum EntityType
 * @brief Represents the different types of entities in the game.
 */
enum EntityType {
    Player_E,            ///< Player-controlled bomber
    AIBomber_E,          ///< AI-controlled bomber
    DestructibleWall_E,  ///< Wall that can be destroyed
    CrumblingWall_E,     ///< Wall in the process of crumbling
    Bomb_E,              ///< A placed bomb
    Explosion_E,         ///< An active explosion
    PowerUp_E,           ///< A collectable power-up
    KnockedOutBomber_E   ///< A bomber in a knocked-out state
};

/**
 * @class Entity
 * @brief Base class for all game entities that interact within the game world.
 * Inherits from Subject to allow observer notifications.
 */
class Entity : public Subject {
public:
    /**
     * @brief Destructor for Entity.
     */
    ~Entity() override = default;

    /**
     * @brief Gets the type of the entity.
     * @return The EntityType.
     */
    [[nodiscard]] virtual EntityType getEntityType() const = 0;

    /**
     * @brief Gets the current position of the entity.
     * @return The Position.
     */
    [[nodiscard]] virtual Position getPosition() const = 0;

    /**
     * @brief Gets the collision rectangle for the entity.
     * @return The collision Rect.
     */
    [[nodiscard]] virtual Rect getCollisionRect() const = 0;

    /**
     * @brief Checks if the entity has been destroyed.
     * @return True if destroyed, false otherwise.
     */
    [[nodiscard]] bool isDestroyed() const { return destroyed; }

    /**
     * @brief Marks the entity as destroyed and notifies observers.
     */
    void destroy() {
        destroyed = true;
        notify(*this, Event::EntityDestroyed);
    }

    /**
     * @brief Updates the entity's logic.
     * @param deltaTime Time elapsed since last update.
     */
    virtual void update(float deltaTime) {}

protected:
    bool destroyed = false; ///< Indicates if the entity is destroyed
};

#endif // BOMBERMAN_COLLIDABLE_H
