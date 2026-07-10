#include "../../../include/logic/factory/BattleStageFactory.h"
#include "../../../include/logic/factory/Player.h"

std::unique_ptr<Player> BattleStageFactory::createPlayer() {
    return std::make_unique<Player>();
}
