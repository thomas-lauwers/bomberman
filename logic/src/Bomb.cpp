#include "logic/Bomb.h"
#include "logic/Stopwatch.h"

namespace logic {

Bomb::Bomb(float x, float y, int range)
    : Entity(x, y), range(range), timer(2.0f), exploded(false), explosionsSpawned(false) {}

void Bomb::update() {
    if (!exploded) {
        timer -= Stopwatch::getInstance().getDeltaTime();
        if (timer <= 0.0f) {
            trigger();
        }
    }
}

bool Bomb::isAlive() const { return !exploded || !explosionsSpawned; }

bool Bomb::hasExploded() const { return exploded; }
bool Bomb::wereExplosionsSpawned() const { return explosionsSpawned; }
void Bomb::setExplosionsSpawned() { explosionsSpawned = true; notify(); }
int Bomb::getRange() const { return range; }

void Bomb::trigger() {
    exploded = true;
    notify();
}

} // namespace logic
