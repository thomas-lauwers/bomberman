#ifndef BOMBERMAN_ARENA_H
#define BOMBERMAN_ARENA_H
#include "Tile.h"
#include <array>
#include <memory>

class Player;

class World {
public:
    static constexpr int HEIGHT = 13;
    static constexpr int WIDTH = 15;

    World();
    ~World();
    void randomizeTiles();

    [[nodiscard]] Tile getTile(int x, int y) const;
    void setTile(int x, int y, Tile tile);
    [[nodiscard]] Player* getPlayer() const;
    void setPlayer(std::unique_ptr<Player> player);

private:
    std::array<std::array<Tile, WIDTH>, HEIGHT> grid;
    std::unique_ptr<Player> player;
};


#endif //BOMBERMAN_ARENA_H
