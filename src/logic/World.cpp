#include "../../include/logic/World.h"
#include "../../include/logic/factory/CrumblingWall.h"
#include "../../include/logic/factory/DestructibleWall.h"
#include "../../include/logic/factory/Explosion.h"
#include "../../include/logic/factory/Player.h"
#include "../../include/utils/Random.h"
#include <algorithm>
#include <cmath>
#include <utility>

World::World(std::shared_ptr<IEntityFactory> factory) : factory(std::move(factory)) {
    using T = TileType;

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            grid[y][x] = Tile(T::E);
        }
    }

    // Initial map layout
    const std::array<std::array<T, WIDTH>, HEIGHT> layout = {
        {{T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W},
         {T::W, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::W},
         {T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W},
         {T::W, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::W},
         {T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W},
         {T::W, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::W},
         {T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W},
         {T::W, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::W},
         {T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W},
         {T::W, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::W},
         {T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W, T::E, T::W},
         {T::W, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::E, T::W},
         {T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W}}};

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            grid[y][x] = Tile(layout[y][x]);
        }
    }

    randomizeTiles();

    player = std::shared_ptr(this->factory->createPlayer());
}

void World::randomizeTiles() {
    // Array of {y, x} coordinates to exclude from randomization
    const std::array<std::array<int, 2>, 12> spawnTiles = {
        {{1, 1}, {2, 1}, {1, 2}, {10, 1}, {11, 1}, {11, 2}, {1, 12}, {1, 13}, {2, 13}, {10, 13}, {11, 13}, {11, 12}}};

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {

            // Check if current (y, x) is in spawnTiles using std::find_if
            const auto it = std::find_if(spawnTiles.begin(), spawnTiles.end(),
                                         [y, x](const std::array<int, 2>& pos) { return pos[0] == y && pos[1] == x; });

            if (it == spawnTiles.end() && getTile(x, y).getType() == TileType::E) {
                if (Random::getInstance().roll(0.80)) {
                    entities.push_back(factory->createDestructibleWall(x, y));
                }
            }
        }
    }
}

Tile World::getTile(const int x, const int y) const { return grid[y][x]; }

void World::setTile(const int x, const int y, const Tile tile) { grid[y][x] = tile; }

std::shared_ptr<Player> World::getPlayer() const { return player; }

void World::setPlayer(std::shared_ptr<Player> player) { this->player = std::move(player); }

const std::vector<std::unique_ptr<Entity>>& World::getEntities() const { return entities; }

void World::pushBackEntity(std::unique_ptr<Entity> entity) { entities.push_back(std::move(entity)); }

void World::removeDestroyedEntities() {
    entities.erase(std::remove_if(entities.begin(), entities.end(),
                                  [](const std::unique_ptr<Entity>& e) { return e->isDestroyed(); }),
                   entities.end());
}

void World::spawnExplosion(const float x, const float y) {
    auto spawnAt = [&](const float px, const float py, const ExplosionType type) {
        const int ix = static_cast<int>(std::round(px));
        const int iy = static_cast<int>(std::round(py));

        if (ix < 0 || ix >= WIDTH || iy < 0 || iy >= HEIGHT)
            return;

        // Destroy destructible walls if in contact
        for (const auto& entity : entities) {
            if (entity->getEntityType() == DestructibleWall_E) {
                Position pos = entity->getPosition();
                if (static_cast<int>(pos.x) == ix && static_cast<int>(pos.y) == iy) {
                    entities.push_back(factory->createCrumblingWall(px, py));
                    entity->destroy();
                    return;
                }
            }
        }

        // Spawn an explosion if tile is empty
        if (getTile(ix, iy).getType() == TileType::E) {
            entities.push_back(factory->createExplosion(px, py, type));
        }
    };

    spawnAt(x, y, ExplosionType::Center);
    spawnAt(x, y + 1.0f, ExplosionType::EndDown);
    spawnAt(x, y - 1.0f, ExplosionType::EndUp);
    spawnAt(x + 1.0f, y, ExplosionType::EndRight);
    spawnAt(x - 1.0f, y, ExplosionType::EndLeft);
}

bool World::isColliding(const Rect& entityRect, const Entity* ignoreEntity, const Rect& currentEntityRect) const {
    const int minX = static_cast<int>(entityRect.x);
    const int maxX = static_cast<int>(entityRect.x + entityRect.width);
    const int minY = static_cast<int>(entityRect.y);
    const int maxY = static_cast<int>(entityRect.y + entityRect.height);

    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            if (getTile(x, y).getType() != TileType::E) {
                Rect tileRect = {static_cast<float>(x), static_cast<float>(y), 1.0f, 1.0f};
                if (entityRect.intersects(tileRect)) {
                    return true;
                }
            }
        }
    }

    for (const auto& entity : entities) {
        // Skip the entity that is calling this check to prevent self-collision
        if (entity.get() == ignoreEntity)
            continue;

        if (entityRect.intersects(entity->getCollisionRect())) {
            if (!(entity->getEntityType() == Bomb_E && currentEntityRect.intersects(entity->getCollisionRect()))) {
                return true;
            }
        }
    }
    return false;
}

bool World::isDestructibleWallAt(const int x, const int y) const {
    for (const auto& entity : entities) {
        if (entity->getEntityType() == DestructibleWall_E) {
            Position pos = entity->getPosition();

            if (static_cast<int>(pos.x) == x && static_cast<int>(pos.y) == y) {
                return true;
            }
        }
    }
    return false;
}

World::~World() = default;
