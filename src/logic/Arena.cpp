#include "../../include/logic/Arena.h"

Arena::Arena() : grid{} {
    using enum TileType;

    grid = {
        {
            {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
            {W, E, E, D, D, D, D, D, D, D, D, D, E, E, W},
            {W, E, W, D, W, D, W, D, W, D, W, D, W, E, W},
            {W, D, D, D, D, D, D, D, D, D, D, D, D, D, W},
            {W, D, W, D, W, D, W, D, W, D, W, D, W, D, W},
            {W, D, D, D, D, D, D, D, D, D, D, D, D, D, W},
            {W, D, W, D, W, D, W, D, W, D, W, D, W, D, W},
            {W, D, D, D, D, D, D, D, D, D, D, D, D, D, W},
            {W, D, W, D, W, D, W, D, W, D, W, D, W, D, W},
            {W, D, D, D, D, D, D, D, D, D, D, D, D, D, W},
            {W, E, W, D, W, D, W, D, W, D, W, D, W, E, W},
            {W, E, E, D, D, D, D, D, D, D, D, D, E, E, W},
            {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
        }
    };

}


TileType Arena::getTile(const int x, const int y) const {
    return grid[x][y];
}

void Arena::setTile(const int x, const int y, const TileType type) {
    grid[x][y] = type;
}

