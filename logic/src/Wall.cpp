#include "logic/Wall.h"

namespace logic {

Wall::Wall(float x, float y, bool destructible)
    : Entity(x, y), destructible(destructible), destroyed(false) {}

void Wall::update() {
    // Walls usually don't do anything on tick
}

bool Wall::isAlive() const { return !destroyed; }

bool Wall::isDestructible() const { return destructible; }

void Wall::destroy() {
    if (destructible) {
        destroyed = true;
        notify();
    }
}

bool Wall::isDestroyed() const { return destroyed; }

} // namespace logic
