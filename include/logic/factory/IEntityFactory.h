/**
 * @file IEntityFactory.h
 * @brief Defines the factory interface for creating game entities.
 */

#ifndef BOMBERMAN_IENTITYFACTORY_H
#define BOMBERMAN_IENTITYFACTORY_H

#include "AIBomber.h"
#include <memory>

class KnockedOutBomber;
class PowerUp;
enum class ExplosionType;
class Explosion;
class CrumblingWall;
class Bomb;
class Player;
class DestructibleWall;
class AIBomber;

/**
 * @class IEntityFactory
 * @brief Abstract interface for creating all types of entities in the game.
 *
 * This factory pattern implementation allows for decoupled entity creation, enabling
 * different implementations (e.g., for different game stages) to be swapped out without
 * modifying the game logic.
 */
class IEntityFactory {
public:
    virtual ~IEntityFactory() = default;

    /**
     * @brief Creates a new player entity.
     * @return Unique pointer to the created player.
     */
    virtual std::unique_ptr<Player> createPlayer() = 0;

    /**
     * @brief Creates a new AI bomber entity.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param type The type of the AI bomber.
     * @return Unique pointer to the created AI bomber.
     */
    virtual std::unique_ptr<AIBomber> createAIBomber(float x, float y, BomberType type) = 0;

    /**
     * @brief Creates a new bomb entity.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param blast_radius The radius of the blast.
     * @return Unique pointer to the created bomb.
     */
    virtual std::unique_ptr<Bomb> createBomb(float x, float y, int blast_radius) = 0;

    /**
     * @brief Creates a new destructible wall entity.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return Unique pointer to the created wall.
     */
    virtual std::unique_ptr<DestructibleWall> createDestructibleWall(float x, float y) = 0;

    /**
     * @brief Creates a new explosion entity.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param type The type of the explosion.
     * @return Unique pointer to the created explosion.
     */
    virtual std::unique_ptr<Explosion> createExplosion(float x, float y, ExplosionType type) = 0;

    /**
     * @brief Creates a new crumbling wall entity.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return Unique pointer to the created crumbling wall.
     */
    virtual std::unique_ptr<CrumblingWall> createCrumblingWall(float x, float y) = 0;

    /**
     * @brief Creates a new power-up entity.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return Unique pointer to the created power-up.
     */
    virtual std::unique_ptr<PowerUp> createPowerUp(float x, float y) = 0;

    /**
     * @brief Creates a new knocked-out bomber entity.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param type The type of the bomber.
     * @return Unique pointer to the created knocked-out bomber.
     */
    virtual std::unique_ptr<KnockedOutBomber> createKnockedOutBomber(float x, float y, BomberType type) = 0;
};

#endif // BOMBERMAN_IENTITYFACTORY_H
