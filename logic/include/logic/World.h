#ifndef BOMBERMAN_LOGIC_WORLD_H
#define BOMBERMAN_LOGIC_WORLD_H

#include <vector>
#include <memory>
#include "Entity.h"
#include "AbstractFactory.h"
#include "Score.h"

namespace logic {

/**
 * @brief Manages all game entities and game rules.
 */
class World {
public:
    World(std::shared_ptr<AbstractFactory> factory);
    ~World();

    /**
     * @brief Update the game state.
     */
    void update();

    /**
     * @brief Initialize the arena with players, enemies, and walls.
     */
    void initArena();

    void addEntity(std::shared_ptr<Entity> entity);
    const std::vector<std::shared_ptr<Entity>>& getEntities() const;

    void movePlayer(float dx, float dy);
    void moveEnemy(Enemy& enemy, float dx, float dy);
    void playerPlaceBomb();

    const Score& getScore() const { return score; }

private:
    void handleCollisions();
    void removeDestroyedEntities();

    void handleExplosionCollision(Entity& explosion, Entity& other);
    void handlePlayerPowerUpCollision(Entity& player, Entity& powerUp);
    bool checkSolidCollision(const Entity& e);
    void spawnExplosions();

    std::shared_ptr<AbstractFactory> factory;
    std::vector<std::shared_ptr<Entity>> entities;
    Score score;
};

} // namespace logic

#endif // BOMBERMAN_LOGIC_WORLD_H
