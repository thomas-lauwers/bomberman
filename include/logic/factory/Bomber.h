/**
 * @file Bomber.h
 * @brief Defines the Bomber class for bomber entities.
 */

#ifndef BOMBERMAN_BOMBER_H
#define BOMBERMAN_BOMBER_H

#include "../../utils/Position.h"
#include "../Observer.h"
#include "../Rect.h"
#include "BomberType.h"
#include "Entity.h"
#include "PowerUp.h"

/**
 * @class Bomber
 * @brief Base class for bomber entities in the game.
 */
class Bomber : public Entity, public Observer {
public:
    Bomber() = default;

    virtual ~Bomber() = default;

    /**
     * @brief Gets the bomber type.
     * @return The BomberType.
     */
    [[nodiscard]] virtual BomberType getBomberType() const = 0;

    /**
     * @brief Sets the position.
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    void setPosition(float x, float y);

    /**
     * @brief Gets the position.
     * @return The Position.
     */
    [[nodiscard]] Position getPosition() const override;

    /**
     * @brief Moves the bomber.
     * @param dx Delta X.
     * @param dy Delta Y.
     */
    void move(float dx, float dy);

    /**
     * @brief Moves the bomber directly.
     * @param dx Delta X.
     * @param dy Delta Y.
     */
    void moveDirectly(float dx, float dy);

    /**
     * @brief Gets the collision rectangle.
     * @return The collision Rect.
     */
    [[nodiscard]] Rect getCollisionRect() const override;

    /**
     * @brief Handles observer notifications.
     * @param entity The source entity.
     * @param event The event type.
     */
    void onNotify(const Entity& entity, Event event) override;

    /**
     * @brief Checks if a bomb can be placed.
     * @return True if can place bomb, false otherwise.
     */
    [[nodiscard]] bool canPlaceBomb() const;

    /**
     * @brief Decrements the number of bombs and sets a cooldown.
     */
    void placeBomb();

    /**
     * @brief Gets the blast radius.
     * @return Blast radius.
     */
    [[nodiscard]] int getBlastRadius() const;

    /**
     * @brief Gains a power-up.
     * @param type PowerUpType.
     */
    void gainPowerUp(PowerUpType type);

    /**
     * @brief Triggers an event.
     * @param event The event type.
     */
    void triggerEvent(Event event);

    /**
     * @brief Updates the bomber.
     * @param deltaTime Time elapsed since last update.
     */
    void update(float deltaTime) override;

protected:
    Position position{1.5f, 1.5f}; ///< Position of the bomber
    float speed = 4.0f;            ///< Speed in units per second
    bool isMoving = false;         ///< Is moving flag
    bool wasMoving = false;        ///< Was moving flag

    int number_of_bombs = 1;          ///< Number of bombs available
    float bomb_cooldown_timer = 0.0f; ///< Bomb cooldown timer
    const float BOMB_COOLDOWN = 0.2f; ///< Bomb cooldown duration

    int blast_radius = 1; ///< Blast radius
};

#endif // BOMBERMAN_BOMBER_H
