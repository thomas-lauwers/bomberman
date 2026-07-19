#ifndef BOMBERMAN_AIBOMBER_H
#define BOMBERMAN_AIBOMBER_H

#include "Bomber.h"
#include "BomberType.h"
#include <vector>
#include <memory>
#include <functional>

class Bomber;
class World;

class AIBomber : public Bomber {
public:
    enum class AIState {
        Fleeing,
        PlacingBomb,
        MovingToPowerUp,
        MovingToEnemy,
        Wandering
    };

    explicit AIBomber(BomberType type);

    [[nodiscard]] EntityType getEntityType() const override;
    [[nodiscard]] BomberType getBomberType() const override;
    [[nodiscard]] BomberType getType() const { return type; }

    void update(float deltaTime, World& world);

    static bool isTileAtRisk(int x, int y, const World& world) ;
    [[nodiscard]] bool isInDanger(const World& world) const;
    bool attemptFlee(const World &world, float deltaTime);

private:
    struct AIBomberObserver : Observer {
        AIBomber* parent;
        explicit AIBomberObserver(AIBomber* p) : parent(p) {}
        void onNotify(const Entity& entity, const Event event) override {
            parent->onNotify(entity, event);
        }
    };

    std::shared_ptr<AIBomberObserver> observer;

    bool attemptPlaceBomb(World& world);
    bool attemptMoveToDestructibleWall(const World &world, float deltaTime);
    bool attemptMoveToPowerUp(const World &world, float deltaTime);
    bool attemptMoveToEnemy(const World &world, float deltaTime);
    bool tryMoveTowards(const World& world, const Position& target, float deltaTime);
    bool executeMovement(const World& world, float dx, float dy);
    
    [[nodiscard]] std::vector<Position> findPathToNearestDestructibleWall(const World& world) const;
    [[nodiscard]] std::vector<Position> findPathToNearestPowerUp(const World& world) const;
    [[nodiscard]] std::vector<Position> findPathToNearestEnemy(const World& world) const;
    std::vector<Position> computePath(const World& world,
                                     const std::function<bool(int, int, const World&)>& isTarget,
                                     const std::function<bool(int, int, const World&)>& isPassable) const;
    [[nodiscard]] bool isNearDestructibleWall(const World& world) const;
    [[nodiscard]] bool isAdjacentToEnemy(const World& world) const;
    [[nodiscard]] bool isNearPowerUp(const World& world) const;
    [[nodiscard]] bool isNearEnemy(const World& world) const;
    [[nodiscard]] bool isPassable(int x, int y, const World& world) const;
    static bool isHitboxFullyInTile(const Position& pos) ;
    [[nodiscard]] bool isTileSafe(int x, int y, const World& world) const;

    [[nodiscard]] std::vector<Position> findPathToNearestSafeTile(const World& world) const;

    BomberType type;
    std::vector<Position> path;
    std::vector<Position> fleePath;
    int pathTimer = 0;
    AIState state = AIState::Wandering;
};

#endif // BOMBERMAN_AIBOMBER_H
