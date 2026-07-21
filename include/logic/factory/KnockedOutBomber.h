/**
 * @file KnockedOutBomber.h
 * @brief Defines the KnockedOutBomber class for bomber entities that have been knocked out.
 */

#ifndef BOMBERMAN_KNOCKEDOUTBOMBER_H
#define BOMBERMAN_KNOCKEDOUTBOMBER_H

#include "AIBomber.h"
#include "Entity.h"

/**
 * @class KnockedOutBomber
 * @brief Represents a bomber entity that is in a knocked-out state.
 */
class KnockedOutBomber : public Entity {
public:
    /**
     * @brief Constructs a KnockedOutBomber instance.
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param type The type of the bomber.
     */
    KnockedOutBomber(float x, float y, BomberType type);

    /**
     * @brief Gets the entity type.
     * @return EntityType::KnockedOutBomber.
     */
    [[nodiscard]] EntityType getEntityType() const override;

    /**
     * @brief Gets the position of the bomber.
     * @return The Position.
     */
    [[nodiscard]] Position getPosition() const override;

    /**
     * @brief Gets the collision rectangle of the bomber.
     * @return The collision Rect.
     */
    [[nodiscard]] Rect getCollisionRect() const override;

    /**
     * @brief Gets the bomber type.
     * @return The BomberType.
     */
    [[nodiscard]] BomberType getBomberType() const { return type; }

    /**
     * @brief Updates the knocked-out bomber's logic.
     * @param deltaTime Time elapsed since last update.
     */
    void update(float deltaTime) override;

private:
    Position position;     ///< The position of the bomber
    BomberType type;       ///< The type of the bomber
    float lifetime = 2.0f; ///< The lifetime of the knocked-out state
};

#endif // BOMBERMAN_KNOCKEDOUTBOMBER_H
