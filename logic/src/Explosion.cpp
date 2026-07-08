#include "logic/Explosion.h"
#include "logic/Stopwatch.h"

namespace logic {

Explosion::Explosion(float x, float y)
    : Entity(x, y), timer(0.5f), finished(false) {}

void Explosion::update() {
    if (!finished) {
        timer -= Stopwatch::getInstance().getDeltaTime();
        if (timer <= 0.0f) {
            finished = true;
            notify();
        }
    }
}

bool Explosion::isAlive() const { return !finished; }

bool Explosion::isFinished() const { return finished; }

} // namespace logic
