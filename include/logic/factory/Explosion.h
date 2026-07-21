/**
 * @file Explosion.h
 * @brief Defines the Explosion class for explosion entities.
 */

#ifndef BOMBERMAN_EXPLOSION_H
#define BOMBERMAN_EXPLOSION_H
#include "Entity.h"

/**
 * @enum ExplosionType
 * @brief Represents the visual type of an explosion segment.
 */
enum class ExplosionType { Center, Horizontal, Vertical, EndUp, EndDown, EndLeft, EndRight };

/**
 * @class Explosion
 * @brief Represents an explosion entity in the game.
 */
class Explosion : public Entity {
public:
    /**
     * @brief Constructs an Explosion instance.
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param type The type of explosion segment.
     */
    Explosion(float x, float y, ExplosionType type);

    /**
     * @brief Gets the entity type.
     * @return EntityType::Explosion.
     */
    [[nodiscard]] EntityType getEntityType() const override;

    /**
     * @brief Gets the position of the explosion.
     * @return The Position.
     */
    [[nodiscard]] Position getPosition() const override;

    /**
     * @brief Gets the collision rectangle of the explosion.
     * @return The collision Rect.
     */
    [[nodiscard]] Rect getCollisionRect() const override;

    /**
     * @brief Gets the type of the explosion.
     * @return The ExplosionType.
     */
    [[nodiscard]] ExplosionType getType() const;

    /**
     * @brief Updates the explosion's logic.
     * @param deltaTime Time elapsed since last update.
     */
    void update(float deltaTime) override;

private:
    Position position;          ///< The position of the explosion
    ExplosionType type;         ///< The type of explosion segment
    float lifetime = 0.6f;      ///< The lifetime of the explosion
};

#endif // BOMBERMAN_EXPLOSION_H
