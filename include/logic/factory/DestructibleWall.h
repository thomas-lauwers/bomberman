/**
 * @file DestructibleWall.h
 * @brief Defines the DestructibleWall class for wall entities that can be destroyed.
 */

#ifndef BOMBERMAN_DESTRUCTIBLEWALL_H
#define BOMBERMAN_DESTRUCTIBLEWALL_H
#include "../../utils/Position.h"
#include "Entity.h"

/**
 * @class DestructibleWall
 * @brief Represents a wall entity that can be destroyed by explosions.
 */
class DestructibleWall : public Entity {
public:
    /**
     * @brief Constructs a DestructibleWall instance.
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    DestructibleWall(float x, float y);

    /**
     * @brief Gets the entity type.
     * @return EntityType::DestructibleWall.
     */
    [[nodiscard]] EntityType getEntityType() const override;

    /**
     * @brief Gets the position of the wall.
     * @return The Position.
     */
    [[nodiscard]] Position getPosition() const override;

    /**
     * @brief Gets the collision rectangle of the wall.
     * @return The collision Rect.
     */
    [[nodiscard]] Rect getCollisionRect() const override;

private:
    Position position; ///< The position of the wall
};

#endif // BOMBERMAN_DESTRUCTIBLEWALL_H
