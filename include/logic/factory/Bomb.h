/**
 * @file Bomb.h
 * @brief Defines the Bomb class for bomb entities.
 */

#ifndef BOMBERMAN_BOMB_H
#define BOMBERMAN_BOMB_H
#include "Entity.h"

/**
 * @class Bomb
 * @brief Represents a bomb entity.
 */
class Bomb : public Entity {
public:
    /**
     * @brief Constructs a Bomb instance.
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param blast_radius The radius of the blast.
     */
    Bomb(float x, float y, int blast_radius);

    /**
     * @brief Gets the entity type.
     * @return EntityType::Bomb.
     */
    [[nodiscard]] EntityType getEntityType() const override;

    /**
     * @brief Gets the position of the bomb.
     * @return The Position.
     */
    [[nodiscard]] Position getPosition() const override;

    /**
     * @brief Gets the collision rectangle of the bomb.
     * @return The collision Rect.
     */
    [[nodiscard]] Rect getCollisionRect() const override;

    /**
     * @brief Gets the blast radius.
     * @return The blast radius.
     */
    [[nodiscard]] int getBlastRadius() const;

    /**
     * @brief Updates the bomb's logic.
     * @param deltaTime Time elapsed since last update.
     */
    void update(float deltaTime) override;

    /**
     * @brief Triggers the bomb's explosion.
     */
    void explode();

    /**
     * @brief Sets whether the bomb was placed by the player.
     * @param val True if placed by player, false otherwise.
     */
    void setPlacedByPlayer(const bool val) { placedByPlayer = val; }

    /**
     * @brief Checks if the bomb was placed by the player.
     * @return True if placed by player, false otherwise.
     */
    [[nodiscard]] bool isPlacedByPlayer() const { return placedByPlayer; }

private:
    Position position;           ///< The position of the bomb
    float timer = 2.0f;          ///< The time until explosion
    int blast_radius;            ///< The radius of the blast
    bool placedByPlayer = false; ///< Indicates if placed by player
};

#endif // BOMBERMAN_BOMB_H
