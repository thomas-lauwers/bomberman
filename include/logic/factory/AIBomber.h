#ifndef BOMBERMAN_AIBOMBER_H
#define BOMBERMAN_AIBOMBER_H

#include "Bomber.h"
#include "BomberType.h"
#include <vector>
#include <memory>

class Bomber;
class World;

class AIBomber : public Bomber {
public:
    enum class AIState {
        Fleeing,
        PlacingBomb,
        MovingToWall,
        Wandering
    };

    explicit AIBomber(BomberType type);

    [[nodiscard]] EntityType getEntityType() const override;
    [[nodiscard]] BomberType getBomberType() const override;
    [[nodiscard]] BomberType getType() const { return type; }

    void update(float deltaTime, World& world);

    bool isTileAtRisk(int x, int y, const World& world) const;
    bool isInDanger(const World& world) const;
    bool attemptFlee(World& world, float deltaTime);

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
    bool attemptMoveToDestructibleWall(const World &world);
    bool tryMoveTowards(const World& world, const Position& target);
    bool executeMovement(const World& world, float dx, float dy);
    
    [[nodiscard]] std::vector<Position> findPathToNearestDestructibleWall(const World& world) const;
    bool isNearDestructibleWall(const World& world) const;

    bool isPassable(int x, int y, const World& world) const;
    bool isTileSafe(int x, int y, const World& world) const;

    std::vector<Position> findPathToNearestSafeTile(const World& world) const;

    BomberType type;
    std::vector<Position> path;
    std::vector<Position> fleePath;
    int pathTimer = 0;
    int stateCheckTimer = 0;
    AIState state = AIState::Wandering;
};

#endif // BOMBERMAN_AIBOMBER_H
