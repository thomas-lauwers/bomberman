#include "../../include/logic/World.h"
#include "../../include/utils/Random.h"
#include "../../include/logic/factory/Player.h"

World::World() {
    using T = TileType;

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            grid[y][x] = Tile(T::E);
        }
    }
    
    // Initial map layout
    const std::array<std::array<T, WIDTH>, HEIGHT> layout = {{
        {T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W},
        {T::W, T::E, T::E, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::E, T::E, T::W},
        {T::W, T::E, T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::E, T::W},
        {T::W, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::W},
        {T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W},
        {T::W, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::W},
        {T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W},
        {T::W, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::W},
        {T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W},
        {T::W, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::W},
        {T::W, T::E, T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::D, T::W, T::E, T::W},
        {T::W, T::E, T::E, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::D, T::E, T::E, T::W},
        {T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W, T::W}
    }};

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            grid[y][x] = Tile(layout[y][x]);
        }
    }

    randomizeTiles();

    player = std::make_unique<Player>();

}

void World::randomizeTiles() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (const Tile tile = getTile(x, y); tile.getType() == TileType::D) {
                if (Random::getInstance().roll(0.20)) {
                    setTile(x, y, Tile(TileType::E));
                }
            }
        }
    }
}


Tile World::getTile(const int x, const int y) const {
    return grid[y][x];
}

void World::setTile(const int x, const int y, const Tile tile) {
    grid[y][x] = tile;
}

Player* World::getPlayer() const {
    return player.get();
}

void World::setPlayer(std::unique_ptr<Player> player) {
    this->player = std::move(player);
}

bool World::isColliding(const Rect &entityRect) const {
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
    return false;
}

World::~World() = default;

