#include "../../include/logic/World.h"
#include "../../include/logic/Random.h"

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

