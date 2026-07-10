#include "../../include/logic/Tile.h"

TileType Tile::getType() const {
    return type;
}

void Tile::setType(const TileType newType) {
    type = newType;
}
