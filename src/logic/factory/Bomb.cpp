#include "../../../include/logic/factory/Bomb.h"
#include "../../../include/utils/Stopwatch.h"
#include <cmath>
#include <iostream>

Bomb::Bomb(const float x, const float y, const int blast_radius) : position{std::round(x), std::round(y)}, blast_radius(blast_radius) {}

EntityType Bomb::getEntityType() const { return Bomb_E; }

Position Bomb::getPosition() const { return position; }

Rect Bomb::getCollisionRect() const { return {position.x, position.y, 1.0f, 1.0f}; }

int Bomb::getBlastRadius() const { return blast_radius; }

void Bomb::update(const float deltaTime) {
    timer -= deltaTime;
    if (timer <= 0) {
        explode();
    }
}

void Bomb::explode() {
    notify(*this, Event::BombExploded);
    destroy();
}
