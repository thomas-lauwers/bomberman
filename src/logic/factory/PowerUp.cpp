#include "../../../include/logic/factory/PowerUp.h"
#include "../../../include/utils/Random.h"

PowerUp::PowerUp(const float x, const float y) : position{x, y} {
    switch (utils::Random::getInstance().getInt()) {
    case 0:
        type = Fire;
        break;

    case 1:
        type = ExtraBomb;
        break;

    case 2:
        type = Skates;
        break;

    default:
        break;
    }
}

EntityType PowerUp::getEntityType() const { return PowerUp_E; }

Position PowerUp::getPosition() const { return position; }

Rect PowerUp::getCollisionRect() const { return {position.x, position.y, 1.0f, 1.0f}; }

PowerUpType PowerUp::getType() const { return type; }
