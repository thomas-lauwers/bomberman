#include <utility>

#include "../../../include/logic/factory/Bomb.h"
#include "../../../include/logic/factory/CrumblingWall.h"
#include "../../../include/logic/factory/DestructibleWall.h"
#include "../../../include/logic/factory/Explosion.h"
#include "../../../include/logic/factory/Player.h"
#include "../../../include/view/entities/PlayerView.h"
#include "../../../include/view/factory/BattleStageFactory.h"
#include "../../../include/logic/factory/PowerUp.h"

void BattleStageFactory::setPlayerView(std::shared_ptr<PlayerView> view) { playerView = std::move(view); }

std::unique_ptr<Player> BattleStageFactory::createPlayer() {
    auto player = std::make_unique<Player>();
    if (playerView) {
        player->addObserver(playerView);
    }
    return player;
}

std::unique_ptr<Bomb> BattleStageFactory::createBomb(float x, float y) {
    auto bomb = std::make_unique<Bomb>(x, y);
    return bomb;
}

std::unique_ptr<DestructibleWall> BattleStageFactory::createDestructibleWall(float x, float y) {
    auto wall = std::make_unique<DestructibleWall>(x, y);
    return wall;
}

std::unique_ptr<Explosion> BattleStageFactory::createExplosion(float x, float y, ExplosionType type) {
    auto explosion = std::make_unique<Explosion>(x, y, type);
    return explosion;
}

std::unique_ptr<CrumblingWall> BattleStageFactory::createCrumblingWall(float x, float y) {
    auto crumblingwall = std::make_unique<CrumblingWall>(x, y);
    return crumblingwall;
}

std::unique_ptr<PowerUp> BattleStageFactory::createPowerUp(float x, float y) {
    auto powerup = std::make_unique<PowerUp>(x, y);
    return powerup;
}