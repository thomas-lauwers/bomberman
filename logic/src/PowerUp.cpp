#include "logic/PowerUp.h"

namespace logic {

PowerUp::PowerUp(float x, float y, PowerUpType type)
    : Entity(x, y), type(type), collected(false) {}

void PowerUp::update() {
    // Check for collection (usually handled by World/Player)
}

bool PowerUp::isAlive() const { return !collected; }

PowerUpType PowerUp::getPowerUpType() const { return type; }

void PowerUp::collect() {
    collected = true;
    notify();
}

bool PowerUp::isCollected() const { return collected; }

} // namespace logic
