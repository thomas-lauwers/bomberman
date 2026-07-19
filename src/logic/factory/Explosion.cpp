#include "../../../include/logic/factory/Explosion.h"
#include "../../../include/utils/Stopwatch.h"
#include <cmath>

Explosion::Explosion(const float x, const float y, const ExplosionType type)
    : position{std::round(x), std::round(y)}, type{type} {}

EntityType Explosion::getEntityType() const { return Explosion_E; }

Position Explosion::getPosition() const { return position; }

Rect Explosion::getCollisionRect() const { return {position.x, position.y, 1.0f, 1.0f}; }

ExplosionType Explosion::getType() const { return type; }

void Explosion::update(const float deltaTime) {
    lifetime -= deltaTime;

    if (lifetime <= 0) {
        destroy();
    }
}
