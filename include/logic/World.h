#ifndef BOMBERMAN_ARENA_H
#define BOMBERMAN_ARENA_H
#include <array>

enum class TileType {
    E, // Empty
    W, // Wall
    D, // Destructible
};

class World {
public:
    static constexpr int HEIGHT = 13;
    static constexpr int WIDTH = 15;

    World();
    void randomizeTiles();

    [[nodiscard]] TileType getTile(int x, int y) const;
    void setTile(int x, int y, TileType type);

private:
    std::array<std::array<TileType, WIDTH>, HEIGHT> grid;
};


#endif //BOMBERMAN_ARENA_H
