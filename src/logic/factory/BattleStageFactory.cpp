#include "../../../include/logic/factory/BattleStageFactory.h"
#include "../../../include/logic/factory/Player.h"
#include "../../../include/logic/factory/Bomb.h"
#include "../../../include/logic/factory/DestructibleWall.h"

std::unique_ptr<Player> BattleStageFactory::createPlayer() {
    return std::make_unique<Player>();
}

std::unique_ptr<Bomb> BattleStageFactory::createBomb(float x, float y) {
    return std::make_unique<Bomb>(x, y);
}

std::unique_ptr<DestructibleWall> BattleStageFactory::createDestructibleWall(float x, float y) {
    return std::make_unique<DestructibleWall>(x, y);
}