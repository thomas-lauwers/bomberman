#ifndef BOMBERMAN_ARENA_H
#define BOMBERMAN_ARENA_H
#include "Tile.h"
#include <array>
#include <memory>
#include <vector>

class Entity;
struct Rect;
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
    [[nodiscard]] const std::vector<std::unique_ptr<Entity>>& getEntities() const;

    void pushBackEntity(std::unique_ptr<Entity> entity);

    [[nodiscard]] bool isColliding(const Rect& entityRect, const Entity* ignoreEntity, const Rect &currentEntityRect) const;
    [[nodiscard]] bool isDestructibleWallAt(int x, int y) const;

private:
    std::array<std::array<Tile, WIDTH>, HEIGHT> grid;
    std::vector<std::unique_ptr<Entity>> entities;
    std::unique_ptr<Player> player;
};


#endif //BOMBERMAN_ARENA_H
