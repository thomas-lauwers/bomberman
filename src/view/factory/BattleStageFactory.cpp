#include "../../../include/logic/factory/Bomb.h"
#include "../../../include/logic/factory/CrumblingWall.h"
#include "../../../include/logic/factory/DestructibleWall.h"
#include "../../../include/logic/factory/Explosion.h"
#include "../../../include/logic/factory/Player.h"
#include "../../../include/view/factory/BattleStageFactory.h"
#include "../../../include/logic/factory/KnockedOutBomber.h"
#include "../../../include/logic/factory/PowerUp.h"

std::unique_ptr<Player> BattleStageFactory::createPlayer() {
    auto player = std::make_unique<Player>();
    player->addObserver(renderer.getPlayerView());
    return player;
}

std::unique_ptr<AIBomber> BattleStageFactory::createAIBomber(const float x, const float y, BomberType type) {
    auto aiBomber = std::make_unique<AIBomber>(type);
    aiBomber->setPosition(x, y);
    const auto view = renderer.createAIBomberView(aiBomber.get(), type);
    aiBomber->addObserver(view);
    return aiBomber;
}

std::unique_ptr<Bomb> BattleStageFactory::createBomb(float x, float y, int blast_radius) {
    auto bomb = std::make_unique<Bomb>(x, y, blast_radius);
    const auto view = renderer.createBombView(bomb.get());
    bomb->addObserver(view);
    return bomb;
}

std::unique_ptr<DestructibleWall> BattleStageFactory::createDestructibleWall(float x, float y) {
    auto wall = std::make_unique<DestructibleWall>(x, y);
    return wall;
}

std::unique_ptr<Explosion> BattleStageFactory::createExplosion(float x, float y, ExplosionType type) {
    auto explosion = std::make_unique<Explosion>(x, y, type);
    const auto view = renderer.createExplosionView(explosion.get());
    explosion->addObserver(view);
    return explosion;
}

std::unique_ptr<CrumblingWall> BattleStageFactory::createCrumblingWall(float x, float y) {
    auto crumblingwall = std::make_unique<CrumblingWall>(x, y);
    const auto view = renderer.createCrumblingWallView(crumblingwall.get());
    crumblingwall->addObserver(view);
    return crumblingwall;
}

std::unique_ptr<PowerUp> BattleStageFactory::createPowerUp(float x, float y) {
    auto powerup = std::make_unique<PowerUp>(x, y);
    const auto view = renderer.createPowerUpView(powerup.get());
    powerup->addObserver(view);
    return powerup;
}

std::unique_ptr<KnockedOutBomber> BattleStageFactory::createKnockedOutBomber(float x, float y, BomberType type) {
    auto knockedoutbomber = std::make_unique<KnockedOutBomber>(x, y, type);
    const auto view = renderer.createKnockedOutBomberView(knockedoutbomber.get(), type);
    knockedoutbomber->addObserver(view);
    return knockedoutbomber;
}
