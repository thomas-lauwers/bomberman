#ifndef BOMBERMAN_TESTENTITYFACTORY_H
#define BOMBERMAN_TESTENTITYFACTORY_H

#include "../include/logic/factory/IEntityFactory.h"
#include "../include/logic/factory/Bomb.h"
#include "../include/logic/factory/DestructibleWall.h"
#include "../include/logic/factory/Explosion.h"
#include "../include/logic/factory/CrumblingWall.h"
#include "../include/logic/factory/KnockedOutBomber.h"
#include "../include/logic/factory/Player.h"
#include "../include/logic/factory/PowerUp.h"

class TestEntityFactory : public IEntityFactory {
public:
    std::unique_ptr<Player> createPlayer() override { return std::make_unique<Player>(); }
    std::unique_ptr<Bomb> createBomb(float x, float y) override { return std::make_unique<Bomb>(x, y); }
    std::unique_ptr<DestructibleWall> createDestructibleWall(float x, float y) override { return std::make_unique<DestructibleWall>(x, y); }
    std::unique_ptr<Explosion> createExplosion(float x, float y, ExplosionType type) override { return std::make_unique<Explosion>(x, y, type); }
    std::unique_ptr<CrumblingWall> createCrumblingWall(float x, float y) override { return std::make_unique<CrumblingWall>(x, y); }
    std::unique_ptr<PowerUp> createPowerUp(float x, float y) override { return std::make_unique<PowerUp>(x, y); }
    std::unique_ptr<KnockedOutBomber> createKnockedOutBomber(float x, float y) override { return std::make_unique<KnockedOutBomber>(x, y); }
};

#endif //BOMBERMAN_TESTENTITYFACTORY_H
