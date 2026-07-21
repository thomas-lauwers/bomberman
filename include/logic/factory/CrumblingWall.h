/**
 * @file CrumblingWall.h
 * @brief Defines the CrumblingWall class for wall entities that are crumbling.
 */

#ifndef BOMBERMAN_CRUMBLINGWALL_H
#define BOMBERMAN_CRUMBLINGWALL_H
#include "Entity.h"

/**
 * @class CrumblingWall
 * @brief Represents a wall entity that is crumbling.
 */
class CrumblingWall : public Entity {
public:
    /**
     * @brief Constructs a CrumblingWall instance.
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    CrumblingWall(float x, float y);

    /**
     * @brief Gets the entity type.
     * @return EntityType::CrumblingWall.
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

    /**
     * @brief Updates the crumbling wall's logic.
     * @param deltaTime Time elapsed since last update.
     */
    void update(float deltaTime) override;

private:
    Position position;    ///< The position of the wall
    float lifetime = 0.75f; ///< The lifetime of the crumbling state
};

#endif // BOMBERMAN_CRUMBLINGWALL_H
