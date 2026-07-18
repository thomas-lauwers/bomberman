#include "../../../include/logic/factory/AIBomber.h"
#include "../../../include/logic/factory/Bomb.h"
#include "../../../include/logic/World.h"
#include <cstdlib>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <utility>

namespace {
    std::pair<int, int> toGrid(Position pos) {
        return {static_cast<int>(std::round(pos.x)), static_cast<int>(std::round(pos.y))};
    }
}

AIBomber::AIBomber(const BomberType type) : observer(std::make_shared<AIBomberObserver>(this)), type{type} {}

EntityType AIBomber::getEntityType() const { return AIBomber_E; }

BomberType AIBomber::getBomberType() const { return type; }

void AIBomber::update(const float deltaTime, World& world) {
    Bomber::update(deltaTime);

    if (attemptFlee(world, deltaTime)) return;
    if (attemptPlaceBomb(world)) return;
    if (canPlaceBomb() && attemptMoveToDestructibleWall(world, deltaTime)) return;
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

bool AIBomber::attemptMoveToDestructibleWall(const World& world, const float deltaTime) {
    if (path.empty() || ++pathTimer > 50) {
        pathTimer = 0;
        path = findPathToNearestDestructibleWall(world);
    }

    if (path.empty()) return false;

    Position currentPos = getPosition();
    Position next = path.front();

    if (std::abs(currentPos.x - next.x) < 0.1 && std::abs(currentPos.y - next.y) < 0.1) {
        path.erase(path.begin());
        if (path.empty()) return false;
        next = path.front();
    }

    if (tryMoveTowards(world, next)) return true;

    return false;
}

bool AIBomber::tryMoveTowards(const World& world, const Position& target) {
    Position currentPos = getPosition();
    float dx = target.x - currentPos.x;
    float dy = target.y - currentPos.y;

    if (std::abs(dx) > std::abs(dy)) {
        if (executeMovement(world, dx > 0 ? 1.0f : -1.0f, 0.0f)) return true;
        if (executeMovement(world, 0.0f, dy > 0 ? 1.0f : -1.0f)) return true;
    } else {
        if (executeMovement(world, 0.0f, dy > 0 ? 1.0f : -1.0f)) return true;
        if (executeMovement(world, dx > 0 ? 1.0f : -1.0f, 0.0f)) return true;
    }
    return false;
}

bool AIBomber::executeMovement(const World& world, const float dx, const float dy) {
    const Rect initialRect = getCollisionRect();
    Position currentPos = getPosition();

    move(dx, dy);
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


std::vector<Position> AIBomber::findPathToNearestDestructibleWall(const World& world) const {
    auto [startX, startY] = toGrid(getPosition());

    std::queue<std::pair<int, int>> q;
    q.emplace(startX, startY);

    std::map<std::pair<int, int>, std::pair<int, int>> parent;
    parent[{startX, startY}] = {-1, -1};

    std::pair target = {-1, -1};

    while (!q.empty()) {
        const std::pair<int, int> current = q.front();
        q.pop();

        if (world.isDestructibleWallAt(current.first + 1, current.second) ||
            world.isDestructibleWallAt(current.first - 1, current.second) ||
            world.isDestructibleWallAt(current.first, current.second + 1) ||
            world.isDestructibleWallAt(current.first, current.second - 1)) {
            target = current;
            break;
        }

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        for (int i = 0; i < 4; ++i) {
            int nx = current.first + dx[i];
            int ny = current.second + dy[i];

            if (nx >= 0 && nx < World::WIDTH && ny >= 0 && ny < World::HEIGHT) {
                Rect rect = {static_cast<float>(nx) + 0.1f, static_cast<float>(ny) + 0.1f, 0.8f, 0.8f};
                if (!world.isColliding(rect, this, getCollisionRect()) && 
                    !isTileAtRisk(nx, ny, world) && 
                    parent.find({nx, ny}) == parent.end()) {
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
            path.push_back({static_cast<float>(current.first), static_cast<float>(current.second)});
            current = parent[current];
        }
        std::reverse(path.begin(), path.end());
    }
    return path;
}
/**
 * Returns true if the bomber is currently standing on a tile that lies
 * within the blast zone of any bomb already on the field.
 */
bool AIBomber::isInDanger(const World& world) const {
    Position pos = getPosition();
    int x = static_cast<int>(std::round(pos.x));
    int y = static_cast<int>(std::round(pos.y));
    return isTileAtRisk(x, y, world);
}

/**
 * Returns true if a bomb’s explosion (cross pattern, radius r) would reach (x,y).
 * Walls are taken into account – the blast is blocked by any wall.
 */
bool AIBomber::isTileAtRisk(int x, int y, const World& world) const {
    if (world.isExplosionAt(x, y)) return true;

    // Retrieve all entities currently in the world.
    const std::vector<std::unique_ptr<Entity>>& entities = world.getEntities();
    for (const auto& entity : entities) {
        if (entity->getEntityType() == Bomb_E) {
            const Bomb* bomb = static_cast<const Bomb*>(entity.get());
            Position bPos = bomb->getPosition();
            int bx = static_cast<int>(std::round(bPos.x));
            int by = static_cast<int>(std::round(bPos.y));
            int r   = bomb->getBlastRadius();

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

/**
 * Checks whether the tile (x,y) is passable (no static collision).
 * The check uses the same collision test as the existing pathfinding.
 */
bool AIBomber::isPassable(int x, int y, const World& world) const {
    if (world.isExplosionAt(x, y)) return false;

    Rect rect = {static_cast<float>(x) + 0.1f,
                 static_cast<float>(y) + 0.1f,
                 0.8f, 0.8f};
    return !world.isColliding(rect, this, getCollisionRect());
}

/**
 * A tile is safe if it is passable and not within any bomb’s blast radius.
 */
bool AIBomber::isTileSafe(int x, int y, const World& world) const {
    return !isTileAtRisk(x, y, world) && isPassable(x, y, world);
}

/**
 * BFS that finds a path from the bomber’s current position to the nearest
 * grid cell that is safe (passable + not in any explosion zone).
 * The search only traverses cells that are themselves safe, so every step
 * of the returned path lies on a safe tile.
 */
std::vector<Position> AIBomber::findPathToNearestSafeTile(const World& world) const {
    auto [startX, startY] = toGrid(getPosition());

    std::queue<std::pair<int, int>> q;
    q.emplace(startX, startY);

    std::map<std::pair<int, int>, std::pair<int, int>> parent;
    parent[{startX, startY}] = {-1, -1};

    std::pair<int, int> target = {-1, -1};

    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();

        // If the current cell is safe, we have found our destination.
        if (isTileSafe(cx, cy, world)) {
            target = {cx, cy};
            break;
        }

        // Expand only into neighbours that are passable.
        const int dx[] = {1, -1, 0, 0};
        const int dy[] = {0, 0, 1, -1};
        for (int i = 0; i < 4; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx >= 0 && nx < World::WIDTH && ny >= 0 && ny < World::HEIGHT) {
                if (isPassable(nx, ny, world) && parent.find({nx, ny}) == parent.end()) {
                    parent[{nx, ny}] = {cx, cy};
                    q.emplace(nx, ny);
                }
            }
        }
    }

    // Reconstruct path from start to the safe cell (target).
    std::vector<Position> path;
    if (target.first != -1) {
        std::pair<int, int> current = target;
        while (current.first != -1) {
            path.push_back({static_cast<float>(current.first),
                            static_cast<float>(current.second)});
            current = parent[current];
        }
        std::reverse(path.begin(), path.end());
    }
    return path;
}

/**
 * Main flee function.
 * If the bomber is inside a danger zone, it will try to move one step
 * along a path towards the nearest safe tile.
 * Returns true if a movement action was successfully executed.
 */
bool AIBomber::attemptFlee(World& world, float deltaTime) {
    // If we are not in danger, only stop if we have finished our flee path.
    if (!isInDanger(world) && fleePath.empty()) {
        return false;
    }

    // Compute a flee path if we don’t have one yet.
    if (fleePath.empty()) {
        fleePath = findPathToNearestSafeTile(world);
        if (fleePath.empty()) {
            // No reachable safe tile – cannot flee.
            return false;
        }
    }

    // Follow the flee path node by node.
    Position currentPos = getPosition();
    Position next = fleePath.front();

    if (std::abs(currentPos.x - next.x) < 0.1 &&
        std::abs(currentPos.y - next.y) < 0.1) {
        fleePath.erase(fleePath.begin());
        if (fleePath.empty()) return false;
        next = fleePath.front();
    }

    if (tryMoveTowards(world, next)) {
        return true;
    }

    // Movement blocked; discard the path so we recompute next frame.
    fleePath.clear();
    return false;
}
