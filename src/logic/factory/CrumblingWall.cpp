#include "../../../include/logic/factory/CrumblingWall.h"

CrumblingWall::CrumblingWall(const float x, const float y) : position{x, y} {}

EntityType CrumblingWall::getEntityType() const { return CrumblingWall_E; }

Position CrumblingWall::getPosition() const { return position; }

Rect CrumblingWall::getCollisionRect() const { return {position.x, position.y, 1.0f, 1.0f}; }

void CrumblingWall::update(const float deltaTime) {
    lifetime -= deltaTime;

    if (lifetime <= 0) {
        destroy();
    }
}
