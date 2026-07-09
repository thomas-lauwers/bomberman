#include "../../include/logic/World.h"
#include "../../include/logic/Random.h"

World::World() : grid{} {
    using T = TileType;

    grid = {{
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

    randomizeTiles();

}

void World::randomizeTiles() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (const TileType type = getTile(x, y); type == TileType::D) {
                if (Random::getInstance().roll(0.20)) {
                    setTile(x, y, TileType::E);
                }
            }
        }
    }
}


TileType World::getTile(const int x, const int y) const {
    return grid[y][x];
}

void World::setTile(const int x, const int y, const TileType type) {
    grid[y][x] = type;
}

