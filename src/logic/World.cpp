#include "../../include/logic/World.h"

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

}


TileType World::getTile(const int x, const int y) const {
    return grid[x][y];
}

void World::setTile(const int x, const int y, const TileType type) {
    grid[x][y] = type;
}

