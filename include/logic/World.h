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

class World : public Observer, public Subject, public std::enable_shared_from_this<World> {
public:
    static constexpr int HEIGHT = 13;
    static constexpr int WIDTH = 15;

    explicit World(std::shared_ptr<IEntityFactory> factory);
    ~World() override;

    void onNotify(const Entity& entity, Event event) override;

    void randomizeTiles();

    [[nodiscard]] Tile getTile(int x, int y) const;
    void setTile(int x, int y, Tile tile);
    [[nodiscard]] std::shared_ptr<Player> getPlayer() const;
    void setPlayer(std::shared_ptr<Player> player);
    [[nodiscard]] const std::vector<std::unique_ptr<Entity>>& getEntities() const;

    void pushBackEntity(std::unique_ptr<Entity> entity);
    void processNewEntities();
    void removeDestroyedEntities();
    void spawnExplosion(float x, float y, int blast_radius, const Bomb* bomb = nullptr);
    void spawnPowerUp(float x, float y);
    void spawnBomb(float x, float y, int blast_radius, const std::weak_ptr<Observer>& observer = {});
    void spawnKnockedOutBomber(float x, float y, BomberType type);

    [[nodiscard]] bool isColliding(const Rect& entityRect, const Entity* ignoreEntity,
                                   const Rect& currentEntityRect) const;
    [[nodiscard]] bool isWallAt(int x, int y) const;
    [[nodiscard]] bool isDestructibleWallAt(int x, int y) const;
    [[nodiscard]] bool isBombAt(float x, float y) const;
    [[nodiscard]] bool isExplosionAt(int x, int y) const;

    void checkExplosionCollision();
    void checkPowerUpsCollection();
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
