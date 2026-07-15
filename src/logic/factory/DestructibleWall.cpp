#include "../../../include/logic/factory/DestructibleWall.h"

DestructibleWall::DestructibleWall(const float x, const float y) : position{x, y} {}

EntityType DestructibleWall::getEntityType() const { return DestructibleWall_E; }

Position DestructibleWall::getPosition() const { return position; }

Rect DestructibleWall::getCollisionRect() const { return {position.x, position.y, 1.0f, 1.0f}; }
