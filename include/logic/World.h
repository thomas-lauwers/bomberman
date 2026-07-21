/**
 * @file World.h
 * @brief Defines the main game world, managing entities and grid layout.
 */

#ifndef BOMBERMAN_ARENA_H
#define BOMBERMAN_ARENA_H
#include "Observer.h"
#include "Subject.h"
#include "Tile.h"
#include "factory/IEntityFactory.h"
#include <array>
#include <memory>
#include <vector>

class Entity;
struct Rect;
class Player;

/**
 * @class World
 * @brief Manages the state of the game world, entities, and tiles.
 *
 * This class acts as the main container for the game arena, handling entity updates,
 * collisions, explosions, and tile management. It inherits from Subject to broadcast events.
 */
class World : public Observer, public Subject, public std::enable_shared_from_this<World> {
public:
    static constexpr int HEIGHT = 13;
    static constexpr int WIDTH = 15;

    /**
     * @brief Constructs a new World instance.
     * @param factory Shared pointer to the entity factory.
     */
    explicit World(std::shared_ptr<IEntityFactory> factory);
    ~World() override;

    /**
     * @brief Handles events notified to the World.
     * @param entity The entity that triggered the event.
     * @param event The event type.
     */
    void onNotify(const Entity& entity, Event event) override;

    /**
     * @brief Randomizes the destructible tiles in the world.
     */
    void randomizeTiles();

    /**
     * @brief Gets the tile at the specified coordinates.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return The Tile at (x, y).
     */
    [[nodiscard]] Tile getTile(int x, int y) const;
    
    /**
     * @brief Sets the tile at the specified coordinates.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param tile The tile to set.
     */
    void setTile(int x, int y, Tile tile);
    
    /**
     * @brief Gets the player entity.
     * @return Shared pointer to the player.
     */
    [[nodiscard]] std::shared_ptr<Player> getPlayer() const;
    
    /**
     * @brief Sets the player entity.
     * @param player Shared pointer to the player.
     */
    void setPlayer(std::shared_ptr<Player> player);
    
    /**
     * @brief Gets all entities in the world.
     * @return A constant reference to the vector of entities.
     */
    [[nodiscard]] const std::vector<std::unique_ptr<Entity>>& getEntities() const;

    /**
     * @brief Adds a new entity to the world.
     * @param entity Unique pointer to the entity to add.
     */
    void pushBackEntity(std::unique_ptr<Entity> entity);

    /**
     * @brief Processes the queue of newly created entities to add them to the world.
     */
    void processNewEntities();

    /**
     * @brief Removes entities marked as destroyed from the world.
     */
    void removeDestroyedEntities();

    /**
     * @brief Spawns an explosion at the specified location.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param blast_radius The radius of the explosion.
     * @param bomb Optional pointer to the bomb that triggered the explosion.
     */
    void spawnExplosion(float x, float y, int blast_radius, const Bomb* bomb = nullptr);

    /**
     * @brief Spawns a power-up at the specified location.
     * @param x The x coordinate.
     * @param y The y coordinate.
     */
    void spawnPowerUp(float x, float y);

    /**
     * @brief Spawns a bomb at the specified location.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param blast_radius The radius of the blast.
     * @param observer Optional weak pointer to the observer of the bomb.
     */
    void spawnBomb(float x, float y, int blast_radius, const std::weak_ptr<Observer>& observer = {});

    /**
     * @brief Spawns a knocked-out bomber at the specified location.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param type The type of the bomber.
     */
    void spawnKnockedOutBomber(float x, float y, BomberType type);

    /**
     * @brief Checks if a given rectangle collides with any entity in the world.
     * @param entityRect The rectangle of the entity to check.
     * @param ignoreEntity Pointer to an entity to ignore during collision check.
     * @param currentEntityRect The current rectangle of the entity.
     * @return True if colliding, false otherwise.
     */
    [[nodiscard]] bool isColliding(const Rect& entityRect, const Entity* ignoreEntity,
                                   const Rect& currentEntityRect) const;

    /**
     * @brief Checks if there is a wall at the specified coordinates.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return True if a wall exists, false otherwise.
     */
    [[nodiscard]] bool isWallAt(int x, int y) const;

    /**
     * @brief Checks if there is a destructible wall at the specified coordinates.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return True if a destructible wall exists, false otherwise.
     */
    [[nodiscard]] bool isDestructibleWallAt(int x, int y) const;

    /**
     * @brief Checks if there is a bomb at the specified coordinates.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return True if a bomb exists, false otherwise.
     */
    [[nodiscard]] bool isBombAt(float x, float y) const;

    /**
     * @brief Checks if there is an explosion at the specified coordinates.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return True if an explosion exists, false otherwise.
     */
    [[nodiscard]] bool isExplosionAt(int x, int y) const;

    /**
     * @brief Checks for collisions between explosions and other entities.
     */
    void checkExplosionCollision();

    /**
     * @brief Checks if any power-ups have been collected by the player or enemies.
     */
    void checkPowerUpsCollection();

    /**
     * @brief Removes the player entity from the world.
     */
    void removePlayer();

private:
    std::array<std::array<Tile, WIDTH>, HEIGHT> grid;
    std::vector<std::unique_ptr<Entity>> entities;
    std::shared_ptr<Player> player;
    std::shared_ptr<IEntityFactory> factory;
    std::vector<Bomb*> bombs_to_explode;
    std::vector<Entity*> entities_to_destroy;
    std::vector<std::unique_ptr<Entity>> new_entities_to_add;
    bool is_processing_explosions = false;
};

#endif // BOMBERMAN_ARENA_H
