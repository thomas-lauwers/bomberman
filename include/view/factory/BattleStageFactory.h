/**
 * @file BattleStageFactory.h
 * @brief Defines the BattleStageFactory class for creating game entities.
 */

#ifndef BOMBERMAN_BATTLESTAGEFACTORY_H
#define BOMBERMAN_BATTLESTAGEFACTORY_H

#include "../../logic/factory/IEntityFactory.h"
#include "../core/WorldRenderer.h"
#include <memory>

/**
 * @class BattleStageFactory
 * @brief Factory class for creating game entities and attaching their view components.
 */
class BattleStageFactory : public IEntityFactory {
public:
    /**
     * @brief Constructs a BattleStageFactory instance.
     * @param t_manager Reference to the texture manager.
     * @param renderer Reference to the world renderer.
     */
    explicit BattleStageFactory(const TextureManager& t_manager, WorldRenderer& renderer)
        : textureManager(t_manager), renderer(renderer) {}

    /** @brief Creates a player entity. @return Unique pointer to the player entity. */
    std::unique_ptr<Player> createPlayer() override;
    /** @brief Creates an AI bomber entity. @param x X coordinate. @param y Y coordinate. @param type The AI bomber type. @return Unique pointer to the AI bomber entity. */
    std::unique_ptr<AIBomber> createAIBomber(float x, float y, BomberType type) override;
    /** @brief Creates a bomb entity. @param x X coordinate. @param y Y coordinate. @param blast_radius The radius of the blast. @return Unique pointer to the bomb entity. */
    std::unique_ptr<Bomb> createBomb(float x, float y, int blast_radius) override;
    /** @brief Creates a destructible wall entity. @param x X coordinate. @param y Y coordinate. @return Unique pointer to the destructible wall entity. */
    std::unique_ptr<DestructibleWall> createDestructibleWall(float x, float y) override;
    /** @brief Creates an explosion entity. @param x X coordinate. @param y Y coordinate. @param type The type of the explosion. @return Unique pointer to the explosion entity. */
    std::unique_ptr<Explosion> createExplosion(float x, float y, ExplosionType type) override;
    /** @brief Creates a crumbling wall entity. @param x X coordinate. @param y Y coordinate. @return Unique pointer to the crumbling wall entity. */
    std::unique_ptr<CrumblingWall> createCrumblingWall(float x, float y) override;
    /** @brief Creates a power-up entity. @param x X coordinate. @param y Y coordinate. @return Unique pointer to the power-up entity. */
    std::unique_ptr<PowerUp> createPowerUp(float x, float y) override;
    /** @brief Creates a knocked-out bomber entity. @param x X coordinate. @param y Y coordinate. @param type The bomber type. @return Unique pointer to the knocked-out bomber entity. */
    std::unique_ptr<KnockedOutBomber> createKnockedOutBomber(float x, float y, BomberType type) override;

private:
    /**
     * @brief Template helper for creating an entity and attaching its view component.
     * @tparam T The type of the entity.
     * @tparam ViewCreator The type of the view creation function.
     * @param entity Unique pointer to the entity.
     * @param viewCreator Function or lambda to create the view component.
     * @return Unique pointer to the set-up entity.
     */
    template <typename T, typename ViewCreator>
    std::unique_ptr<T> createEntity(std::unique_ptr<T> entity, ViewCreator&& viewCreator) {
        const auto view = viewCreator(entity.get());
        entity->addObserver(view);
        return entity;
    }

    const TextureManager& textureManager; ///< Reference to the texture manager
    WorldRenderer& renderer;              ///< Reference to the world renderer
};

#endif // BOMBERMAN_BATTLESTAGEFACTORY_H
