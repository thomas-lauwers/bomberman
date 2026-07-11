#include "../../../include/logic/factory/Bomb.h"

#include <cmath>

Bomb::Bomb(const float x, const float y) : position{std::round(x), std::round(y)} {}

EntityType Bomb::getEntityType() const {
    return Bomb_E;
}

Position Bomb::getPosition() const {
    return position;
}

Rect Bomb::getCollisionRect() const {
    return {position.x, position.y, 1.0f, 1.0f};
}
