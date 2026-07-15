#ifndef BOMBERMAN_IENTITYFACTORY_H
#define BOMBERMAN_IENTITYFACTORY_H

#include <memory>

enum class ExplosionType;
class Explosion;
class CrumblingWall;
class Bomb;
class Player;
class DestructibleWall;

class IEntityFactory {
public:
    virtual ~IEntityFactory() = default;

    virtual std::unique_ptr<Player> createPlayer() = 0;
    virtual std::unique_ptr<Bomb> createBomb(float x, float y) = 0;
    virtual std::unique_ptr<DestructibleWall> createDestructibleWall(float x, float y) = 0;
    virtual std::unique_ptr<Explosion> createExplosion(float x, float y, ExplosionType type) = 0;
    virtual std::unique_ptr<CrumblingWall> createCrumblingWall(float x, float y) = 0;
};


#endif //BOMBERMAN_IENTITYFACTORY_H
