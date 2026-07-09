#include "include/logic/state/PlayState.h"
#include "include/logic/World.h"
#include "include/view/Game.h"
#include "include/view/WorldRenderer.h"

int main() {
    Game g;
    g.addGameState(make_unique<PlayState>());
    g.run();
    return 0;
}
