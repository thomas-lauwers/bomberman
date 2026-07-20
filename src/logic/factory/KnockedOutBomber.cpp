#include "../../../include/logic/factory/KnockedOutBomber.h"

KnockedOutBomber::KnockedOutBomber(const float x, const float y, const BomberType type) : position{x, y}, type{type} {}

EntityType KnockedOutBomber::getEntityType() const { return KnockedOutBomber_E; }

Position KnockedOutBomber::getPosition() const { return position; }

// Allow collision by setting width and height to 0
Rect KnockedOutBomber::getCollisionRect() const { return {position.x, position.y, 0.0f, 0.0f}; }

void KnockedOutBomber::update(const float deltaTime) {
    lifetime -= deltaTime;

    if (lifetime <= 0) {
        destroy();
    }
}