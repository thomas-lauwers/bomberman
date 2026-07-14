#include "../../../include/view/factory/BattleStageFactory.h"
#include "../../../include/logic/factory/Player.h"
#include "../../../include/logic/factory/Bomb.h"
#include "../../../include/logic/factory/DestructibleWall.h"
#include "../../../include/view/PlayerView.h"
#include "../../../include/view/BombView.h"
#include "../../../include/view/DestructibleWallView.h"
#include "../../../include/view/ExplosionView.h"

void BattleStageFactory::setPlayerView(std::shared_ptr<PlayerView> view) {
    playerView = view;
}

std::unique_ptr<Player> BattleStageFactory::createPlayer() {
    auto player = std::make_unique<Player>();
    if (playerView) {
        player->addObserver(playerView);
    }
    return player;
}

std::unique_ptr<Bomb> BattleStageFactory::createBomb(float x, float y) {
    auto bomb = std::make_unique<Bomb>(x, y);
    bomb->addObserver(std::make_shared<BombView>(textureManager));
    return bomb;
}

std::unique_ptr<DestructibleWall> BattleStageFactory::createDestructibleWall(float x, float y) {
    auto wall = std::make_unique<DestructibleWall>(x, y);
    wall->addObserver(std::make_shared<DestructibleWallView>(textureManager));
    return wall;
}

std::unique_ptr<Explosion> BattleStageFactory::createExplosion(float x, float y, ExplosionType type) {
    auto explosion = std::make_unique<Explosion>(x, y, type);
    explosion->addObserver(std::make_shared<ExplosionView>(textureManager));
    return explosion;
}