#ifndef BOMBERMAN_ARENA_H
#define BOMBERMAN_ARENA_H
#include "Tile.h"
#include <array>

class World {
public:
    static constexpr int HEIGHT = 13;
    static constexpr int WIDTH = 15;

    World();
    void randomizeTiles();

    [[nodiscard]] Tile getTile(int x, int y) const;
    void setTile(int x, int y, Tile tile);

private:
    std::array<std::array<Tile, WIDTH>, HEIGHT> grid;
};


#endif //BOMBERMAN_ARENA_H
