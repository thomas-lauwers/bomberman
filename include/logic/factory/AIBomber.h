/**
 * @file AIBomber.h
 * @brief Defines the AIBomber class for AI-controlled bomber entities.
 */

#ifndef BOMBERMAN_AIBOMBER_H
#define BOMBERMAN_AIBOMBER_H

#include "Bomber.h"
#include "BomberType.h"
#include <functional>
#include <memory>
#include <vector>

class Bomber;
class World;

/**
 * @class AIBomber
 * @brief Represents an AI-controlled bomber entity.
 */
class AIBomber : public Bomber {
public:
    /**
     * @enum AIState
     * @brief Possible states for the AI behavior.
     */
    enum class AIState { Fleeing, PlacingBomb, MovingToPowerUp, MovingToEnemy, Wandering };

    /**
     * @brief Constructs an AIBomber instance.
     * @param type The type of bomber.
     */
    explicit AIBomber(BomberType type);

    /**
     * @brief Gets the entity type.
     * @return EntityType::AIBomber.
     */
    [[nodiscard]] EntityType getEntityType() const override;

    /**
     * @brief Gets the bomber type.
     * @return The BomberType.
     */
    [[nodiscard]] BomberType getBomberType() const override;

    /**
     * @brief Gets the type of the bomber.
     * @return The BomberType.
     */
    [[nodiscard]] BomberType getType() const { return type; }

    /**
     * @brief Updates the AI bomber's logic.
     * @param deltaTime Time elapsed since last update.
     * @param world The game world.
     */
    void update(float deltaTime, World& world);

    /**
     * @brief Checks if a tile is at risk from explosions.
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param world The game world.
     * @return True if at risk, false otherwise.
     */
    static bool isTileAtRisk(int x, int y, const World& world);

    /**
     * @brief Checks if the bomber is in danger.
     * @param world The game world.
     * @return True if in danger, false otherwise.
     */
    [[nodiscard]] bool isInDanger(const World& world) const;

    /**
     * @brief Attempts to flee from danger.
     * @param world The game world.
     * @param deltaTime Time elapsed since last update.
     * @return True if successfully moved towards safety, false otherwise.
     */
    bool attemptFlee(const World& world, float deltaTime);

    /**
     * @brief Checks if near an enemy.
     * @param world The game world.
     * @return True if near enemy, false otherwise.
     */
    [[nodiscard]] bool isNearEnemy(const World& world) const;

private:
    struct AIBomberObserver : Observer {
        AIBomber* parent;
        explicit AIBomberObserver(AIBomber* p) : parent(p) {}
        void onNotify(const Entity& entity, const Event event) override { parent->onNotify(entity, event); }
    };

    std::shared_ptr<AIBomberObserver> observer;

    bool attemptPlaceBomb(World& world);
    bool attemptMoveToDestructibleWall(const World& world, float deltaTime);
    bool attemptMoveToPowerUp(const World& world, float deltaTime);
    bool attemptMoveToEnemy(const World& world, float deltaTime);
    bool advanceAlongPath(const World& world, float deltaTime);
    bool tryMoveTowards(const World& world, const Position& target, float deltaTime);
    bool executeMovement(const World& world, float dx, float dy);

    [[nodiscard]] std::vector<Position> findPathToNearestDestructibleWall(const World& world) const;
    [[nodiscard]] std::vector<Position> findPathToNearestPowerUp(const World& world) const;
    [[nodiscard]] std::vector<Position> findPathToNearestEnemy(const World& world) const;
    std::vector<Position> computePath(const World& world, const std::function<bool(int, int, const World&)>& isTarget,
                                      const std::function<bool(int, int, const World&)>& isPassable) const;
    [[nodiscard]] bool isNearDestructibleWall(const World& world) const;
    [[nodiscard]] bool isAdjacentToEnemy(const World& world) const;
    [[nodiscard]] bool isNearPowerUp(const World& world) const;
    [[nodiscard]] bool isPassable(int x, int y, const World& world) const;
    static bool isHitboxFullyInTile(const Position& pos);
    [[nodiscard]] bool isTileSafe(int x, int y, const World& world) const;

    [[nodiscard]] std::vector<Position> findPathToNearestSafeTile(const World& world) const;

    static constexpr int AI_STATE_REEVALUATION_INTERVAL = 10;
    BomberType type;
    std::vector<Position> path;
    std::vector<Position> fleePath;
    int pathTimer = 0;
    int aiStateTimer = 0;
    AIState state = AIState::Wandering;
};

#endif // BOMBERMAN_AIBOMBER_H
