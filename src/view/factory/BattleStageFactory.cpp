#include "../../../include/view/factory/BattleStageFactory.h"
#include "../../../include/logic/factory/Bomb.h"
#include "../../../include/logic/factory/CrumblingWall.h"
#include "../../../include/logic/factory/DestructibleWall.h"
#include "../../../include/logic/factory/Explosion.h"
#include "../../../include/logic/factory/KnockedOutBomber.h"
#include "../../../include/logic/factory/Player.h"
#include "../../../include/logic/factory/PowerUp.h"

std::unique_ptr<Player> BattleStageFactory::createPlayer() {
    return createEntity(std::make_unique<Player>(), [this](Player*) { return renderer.getPlayerView(); });
}

std::unique_ptr<AIBomber> BattleStageFactory::createAIBomber(const float x, const float y, BomberType type) {
    auto aiBomber = std::make_unique<AIBomber>(type);
    aiBomber->setPosition(x, y);
    return createEntity(std::move(aiBomber),
                        [this, type](const AIBomber* e) { return renderer.createAIBomberView(e, type); });
}

std::unique_ptr<Bomb> BattleStageFactory::createBomb(float x, float y, int blast_radius) {
    return createEntity(std::make_unique<Bomb>(x, y, blast_radius),
                        [this](const Bomb* e) { return renderer.createBombView(e); });
}

std::unique_ptr<DestructibleWall> BattleStageFactory::createDestructibleWall(float x, float y) {
    auto wall = std::make_unique<DestructibleWall>(x, y);
    return wall;
}

std::unique_ptr<Explosion> BattleStageFactory::createExplosion(float x, float y, ExplosionType type) {
    return createEntity(std::make_unique<Explosion>(x, y, type),
                        [this](const Explosion* e) { return renderer.createExplosionView(e); });
}

std::unique_ptr<CrumblingWall> BattleStageFactory::createCrumblingWall(float x, float y) {
    return createEntity(std::make_unique<CrumblingWall>(x, y),
                        [this](const CrumblingWall* e) { return renderer.createCrumblingWallView(e); });
}

std::unique_ptr<PowerUp> BattleStageFactory::createPowerUp(float x, float y) {
    return createEntity(std::make_unique<PowerUp>(x, y),
                        [this](const PowerUp* e) { return renderer.createPowerUpView(e); });
}

std::unique_ptr<KnockedOutBomber> BattleStageFactory::createKnockedOutBomber(float x, float y, BomberType type) {
    return createEntity(std::make_unique<KnockedOutBomber>(x, y, type), [this, type](const KnockedOutBomber* e) {
        return renderer.createKnockedOutBomberView(e, type);
    });
}
