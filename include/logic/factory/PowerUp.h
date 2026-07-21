/**
 * @file PowerUp.h
 * @brief Defines the PowerUp class for collectable power-ups.
 */

#ifndef BOMBERMAN_POWERUP_H
#define BOMBERMAN_POWERUP_H
#include "../../utils/Position.h"
#include "Entity.h"

/**
 * @enum PowerUpType
 * @brief Represents the types of power-ups available in the game.
 */
enum PowerUpType { Fire, ExtraBomb, Skates };

/**
 * @class PowerUp
 * @brief Represents a collectable power-up entity.
 */
class PowerUp : public Entity {
public:
    /**
     * @brief Constructs a PowerUp instance.
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    PowerUp(float x, float y);

    /**
     * @brief Gets the entity type.
     * @return EntityType::PowerUp.
     */
    [[nodiscard]] EntityType getEntityType() const override;
    
    /**
     * @brief Gets the position of the power-up.
     * @return The Position.
     */
    [[nodiscard]] Position getPosition() const override;
    
    /**
     * @brief Gets the collision rectangle of the power-up.
     * @return The collision Rect.
     */
    [[nodiscard]] Rect getCollisionRect() const override;
    
    /**
     * @brief Gets the type of the power-up.
     * @return The PowerUpType.
     */
    [[nodiscard]] PowerUpType getType() const;

private:
    Position position; ///< The position of the power-up
    PowerUpType type;  ///< The type of the power-up
};

#endif // BOMBERMAN_POWERUP_H
