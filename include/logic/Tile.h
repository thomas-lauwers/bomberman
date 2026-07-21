/**
 * @file Tile.h
 * @brief Defines the Tile class and TileType enum for the game grid.
 */

#ifndef BOMBERMAN_TILE_H
#define BOMBERMAN_TILE_H

/**
 * @enum TileType
 * @brief Represents the types of tiles in the game grid.
 */
enum class TileType {
    E, ///< Empty
    W, ///< Wall
};

/**
 * @class Tile
 * @brief Represents a single tile in the game grid.
 */
class Tile {
public:
    /**
     * @brief Constructs a new Tile instance.
     * @param type The type of the tile (defaults to Empty).
     */
    explicit Tile(const TileType type = TileType::E) : type(type) {}

    /**
     * @brief Gets the type of the tile.
     * @return The TileType of this tile.
     */
    [[nodiscard]] TileType getType() const;

    /**
     * @brief Sets the type of the tile.
     * @param newType The new TileType for this tile.
     */
    void setType(TileType newType);

private:
    TileType type; ///< The type of the tile
};

#endif // BOMBERMAN_TILE_H
