#include "../../../include/logic/factory/AIBomber.h"
#include "../../../include/logic/factory/Bomb.h"
#include "../../../include/logic/World.h"
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <utility>

namespace {
    std::pair<int, int> toGrid(const Position pos) {
        return {static_cast<int>(std::floor(pos.x)), static_cast<int>(std::floor(pos.y))};
    }
}

AIBomber::AIBomber(const BomberType type) : observer(std::make_shared<AIBomberObserver>(this)), type{type} {}

EntityType AIBomber::getEntityType() const { return AIBomber_E; }

BomberType AIBomber::getBomberType() const { return type; }

void AIBomber::update(const float deltaTime, World& world) {
    Bomber::update(deltaTime);

    std::cout << "[";
    for (auto it : fleePath) {
        std::cout << "(" << it.x << ", " << it.y << "), ";
    }

    std::cout << "]" << std::endl;

    if (isInDanger(world)) {
        state = AIState::Fleeing;
    } else {
        fleePath.clear();
        if (isNearPowerUp(world)) {
            state = AIState::MovingToPowerUp;
        } else if (canPlaceBomb() && isNearDestructibleWall(world)) {
            state = AIState::PlacingBomb;
        } else {
            state = AIState::Wandering;
        }
    }

    switch (state) {
        case AIState::Fleeing:
            attemptFlee(world, deltaTime);
            break;
        case AIState::PlacingBomb:
            attemptPlaceBomb(world);
            break;
        case AIState::MovingToPowerUp:
            attemptMoveToPowerUp(world, deltaTime);
            break;
        case AIState::Wandering:
            attemptMoveToDestructibleWall(world, deltaTime);
            break;
    }
}

bool AIBomber::attemptPlaceBomb(World& world) {
    Position pos = getPosition();
    auto [x, y] = toGrid(pos);

    if (world.isDestructibleWallAt(x + 1, y) || world.isDestructibleWallAt(x - 1, y) ||
        world.isDestructibleWallAt(x, y + 1) || world.isDestructibleWallAt(x, y - 1)) {
        if (canPlaceBomb() && !world.isBombAt(pos.x, pos.y)) {
            world.spawnBomb(pos.x, pos.y, getBlastRadius(), observer);
            placeBomb();
            return true;
        }
    }
    return false;
}

bool AIBomber::attemptMoveToDestructibleWall(const World &world, float deltaTime) {
    if (path.empty() || ++pathTimer > 50) {
        pathTimer = 0;
        path = findPathToNearestDestructibleWall(world);
    }

    if (path.empty()) return false;

    Position currentPos = getPosition();
    Position next = path.front();

    // Direction to the target
    float dx = next.x - currentPos.x;
    float dy = next.y - currentPos.y;

    // Check if we are already past the target node in the direction of movement
    bool pastX = (dx > 0 && currentPos.x > next.x) || (dx < 0 && currentPos.x < next.x);
    bool pastY = (dy > 0 && currentPos.y > next.y) || (dy < 0 && currentPos.y < next.y);

    if (pastX || pastY || isHitboxFullyInTile(currentPos)) {
        path.erase(path.begin());
        if (path.empty()) return false;
        next = path.front();
    }

    return tryMoveTowards(world, next, deltaTime);
}

bool AIBomber::tryMoveTowards(const World& world, const Position& target, float deltaTime) {
    Position currentPos = getPosition();
    float dx = target.x - currentPos.x;
    float dy = target.y - currentPos.y;
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist < 0.001f) return true; // Already there

    float moveSpeed = speed; // Assuming 'speed' is a member variable
    float step = std::min(dist, moveSpeed * deltaTime);

    float moveX = (dx / dist) * step;
    float moveY = (dy / dist) * step;

    return executeMovement(world, moveX, moveY);
}

bool AIBomber::isNearDestructibleWall(const World& world) const {
    Position pos = getPosition();
    auto [x, y] = toGrid(pos);
    const int dx[] = {1, -1, 0, 0};
    const int dy[] = {0, 0, 1, -1};
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (world.isDestructibleWallAt(nx, ny) && !isTileAtRisk(nx, ny, world)) {
            return true;
        }
    }
    return false;
}

bool AIBomber::executeMovement(const World& world, const float dx, const float dy) {
    const Rect initialRect = getCollisionRect();
    Position currentPos = getPosition();

    moveDirectly(dx, dy);
    if (world.isColliding(getCollisionRect(), this, initialRect)) {
        setPosition(currentPos.x, currentPos.y);
        return false;
    } else {
        if (dx > 0) triggerEvent(Event::BomberMovedRight);
        else if (dx < 0) triggerEvent(Event::BomberMovedLeft);
        else if (dy > 0) triggerEvent(Event::BomberMovedDown);
        else if (dy < 0) triggerEvent(Event::BomberMovedUp);
        return true;
    }
}



std::vector<Position> AIBomber::computePath(const World& world,
                                           const std::function<bool(int, int, const World&)>& isTarget,
                                           const std::function<bool(int, int, const World&)>& isPassable) const {
    auto [startX, startY] = toGrid(getPosition());

    std::queue<std::pair<int, int>> q;
    q.emplace(startX, startY);

    std::map<std::pair<int, int>, std::pair<int, int>> parent;
    parent[{startX, startY}] = {-1, -1};

    std::pair target = {-1, -1};

    while (!q.empty()) {
        const std::pair<int, int> current = q.front();
        q.pop();

        if (isTarget(current.first, current.second, world)) {
            target = current;
            break;
        }

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        for (int i = 0; i < 4; ++i) {
            int nx = current.first + dx[i];
            int ny = current.second + dy[i];

            if (nx >= 0 && nx < World::WIDTH && ny >= 0 && ny < World::HEIGHT) {
                if (isPassable(nx, ny, world) && parent.find({nx, ny}) == parent.end()) {
                    parent[{nx, ny}] = current;
                    q.push({nx, ny});
                }
            }
        }
    }

    std::vector<Position> path;
    if (target.first != -1) {
        std::pair<int, int> current = target;
        while (current.first != -1) {
            path.push_back({static_cast<float>(current.first) + 0.5f, static_cast<float>(current.second) + 0.5f});
            current = parent[current];
        }
        std::reverse(path.begin(), path.end());
    }
    return path;
}

std::vector<Position> AIBomber::findPathToNearestDestructibleWall(const World& world) const {
    auto isTarget = [this](int cx, int cy, const World& world) {
        return (world.isDestructibleWallAt(cx + 1, cy) && !isTileAtRisk(cx + 1, cy, world)) ||
               (world.isDestructibleWallAt(cx - 1, cy) && !isTileAtRisk(cx - 1, cy, world)) ||
               (world.isDestructibleWallAt(cx, cy + 1) && !isTileAtRisk(cx, cy + 1, world)) ||
               (world.isDestructibleWallAt(cx, cy - 1) && !isTileAtRisk(cx, cy - 1, world));
    };
    auto isPassable = [this](int nx, int ny, const World& world) {
        Rect rect = {(nx + 0.1f), (ny + 0.1f), 0.8f, 0.8f};
        return !world.isColliding(rect, this, getCollisionRect()) && !isTileAtRisk(nx, ny, world);
    };

    return computePath(world, isTarget, isPassable);
}

bool AIBomber::isInDanger(const World& world) const {
    Position pos = getPosition();
    // Assuming a 0.8x0.8 hitbox, the distance from center to edge is 0.4.
    float halfSize = 0.46f;

    // Calculate the range of grid tiles that the hitbox overlaps
    int minX = static_cast<int>(std::floor(pos.x - halfSize));
    int maxX = static_cast<int>(std::floor(pos.x + halfSize));
    int minY = static_cast<int>(std::floor(pos.y - halfSize));
    int maxY = static_cast<int>(std::floor(pos.y + halfSize));

    // Check if any of the tiles covered by the hitbox are in danger
    for (int x = minX; x <= maxX; ++x) {
        for (int y = minY; y <= maxY; ++y) {
            // Check if this specific tile is at risk
            if (isTileAtRisk(x, y, world)) {
                return true; // The AI is in danger if any part of it is.
            }
        }
    }
    return false;
}

bool AIBomber::isTileAtRisk(int x, int y, const World& world) const {
    if (world.isExplosionAt(x, y)) return true;

    // Retrieve all entities currently in the world.
    const std::vector<std::unique_ptr<Entity>>& entities = world.getEntities();
    for (const auto& entity : entities) {
        if (entity->getEntityType() == Bomb_E) {
            const Bomb* bomb = static_cast<const Bomb*>(entity.get());
            Position bPos = bomb->getPosition();
            const int bx = static_cast<int>(bPos.x);
            const int by = static_cast<int>(bPos.y);
            const int r = bomb->getBlastRadius();

            if (bx == x && by == y) return true;

            // Check 4 directions
            const int dx[] = {1, -1, 0, 0};
            const int dy[] = {0, 0, 1, -1};

            for (int i = 0; i < 4; ++i) {
                for (int dist = 1; dist <= r; ++dist) {
                    int nx = bx + dx[i] * dist;
                    int ny = by + dy[i] * dist;

                    if (nx == x && ny == y) return true; // Target IS at risk!

                    if (world.isWallAt(nx, ny)) break; // Blast is blocked by this wall
                }
            }
        }
    }
    return false;
}


bool AIBomber::isHitboxFullyInTile(const Position& pos) const {
    const int gridX = static_cast<int>(std::floor(pos.x));
    const int gridY = static_cast<int>(std::floor(pos.y));
    const float halfSize = 0.46f;
    return (pos.x - halfSize >= static_cast<float>(gridX) &&
            pos.x + halfSize <= static_cast<float>(gridX) + 1.0f &&
            pos.y - halfSize >= static_cast<float>(gridY) &&
            pos.y + halfSize <= static_cast<float>(gridY) + 1.0f);
}

bool AIBomber::isPassable(int x, int y, const World& world) const {
    if (world.isExplosionAt(x, y)) return false;

    Rect rect = {static_cast<float>(x) + 0.1f,
                 static_cast<float>(y) + 0.1f,
                 0.8f, 0.8f};
    return !world.isColliding(rect, this, getCollisionRect());
}

bool AIBomber::isTileSafe(int x, int y, const World& world) const {
    return !isTileAtRisk(x, y, world) && isPassable(x, y, world);
}

std::vector<Position> AIBomber::findPathToNearestSafeTile(const World& world) const {
    auto isTarget = [this](int cx, int cy, const World& world) {
        return isTileSafe(cx, cy, world);
    };
    auto isPassable = [this](int nx, int ny, const World& world) {
        return this->isPassable(nx, ny, world);
    };

    return computePath(world, isTarget, isPassable);
}

bool AIBomber::attemptFlee(World &world, float deltaTime) {
    // If we are not in danger, only stop if we have finished our flee path.
    if (!isInDanger(world) && fleePath.empty()) {
        return false;
    }

    // Compute a flee path if we don’t have one yet.
    if (fleePath.empty()) {
        fleePath = findPathToNearestSafeTile(world);
        if (fleePath.empty()) {
            // No reachable safe tile – cannot flee.
            return true;
        }
    }

    Position currentPos = getPosition();
    Position next = fleePath.front();

    // Direction to the target
    float dx = next.x - currentPos.x;
    float dy = next.y - currentPos.y;

    // Check if we are already past the target node in the direction of movement
    bool pastX = (dx > 0 && currentPos.x > next.x) || (dx < 0 && currentPos.x < next.x);
    bool pastY = (dy > 0 && currentPos.y > next.y) || (dy < 0 && currentPos.y < next.y);

    if (pastX || pastY || isHitboxFullyInTile(currentPos)) {
        fleePath.erase(fleePath.begin());
        if (fleePath.empty()) return false;
        next = fleePath.front();
    }

    return tryMoveTowards(world, next, deltaTime);
}

bool AIBomber::isNearPowerUp(const World& world) const {
    return !findPathToNearestPowerUp(world).empty();
}

std::vector<Position> AIBomber::findPathToNearestPowerUp(const World& world) const {
    auto isTarget = [](int cx, int cy, const World& world) {
        const auto& entities = world.getEntities();
        for (const auto& entity : entities) {
            if (entity->getEntityType() == PowerUp_E) {
                auto [px, py] = toGrid(entity->getPosition());
                if (px == cx && py == cy) return true;
            }
        }
        return false;
    };
    auto isPassable = [this](int nx, int ny, const World& world) {
        Rect rect = {(nx + 0.1f), (ny + 0.1f), 0.8f, 0.8f};
        return !world.isColliding(rect, this, getCollisionRect()) && !isTileAtRisk(nx, ny, world);
    };

    return computePath(world, isTarget, isPassable);
}

bool AIBomber::attemptMoveToPowerUp(const World &world, float deltaTime) {
    if (path.empty() || ++pathTimer > 50) {
        pathTimer = 0;
        path = findPathToNearestPowerUp(world);
    }

    if (path.empty()) return false;

    Position currentPos = getPosition();
    Position next = path.front();

    // Direction to the target
    float dx = next.x - currentPos.x;
    float dy = next.y - currentPos.y;

    // Check if we are already past the target node in the direction of movement
    bool pastX = (dx > 0 && currentPos.x > next.x) || (dx < 0 && currentPos.x < next.x);
    bool pastY = (dy > 0 && currentPos.y > next.y) || (dy < 0 && currentPos.y < next.y);

    if (pastX || pastY || isHitboxFullyInTile(currentPos)) {
        path.erase(path.begin());
        if (path.empty()) return false;
        next = path.front();
    }

    return tryMoveTowards(world, next, deltaTime);
}