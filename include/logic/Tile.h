#ifndef BOMBERMAN_TILE_H
#define BOMBERMAN_TILE_H

enum class TileType {
    E, // Empty
    W, // Wall
    D, // Destructible
};

class Tile {
public:
    explicit Tile(const TileType type = TileType::E) : type(type) {}

    [[nodiscard]] TileType getType() const;

    void setType(TileType newType);

private:
    TileType type;
};

#endif //BOMBERMAN_TILE_H
