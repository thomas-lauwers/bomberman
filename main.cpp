#include "include/logic/state/PlayState.h"
#include "include/logic/World.h"
#include "include/view/Game.h"
#include "include/view/WorldRenderer.h"
#include "include/logic/factory/BattleStageFactory.h"
#include <memory>

int main() {
    Game g;
    g.addGameState(std::make_unique<PlayState>(std::make_unique<BattleStageFactory>()));
    g.run();
    return 0;
}
