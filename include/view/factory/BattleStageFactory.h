#ifndef BOMBERMAN_BATTLESTAGEFACTORY_H
#define BOMBERMAN_BATTLESTAGEFACTORY_H

#include "../../logic/factory/IEntityFactory.h"
#include "../core/WorldRenderer.h"
#include <memory>

class BattleStageFactory : public IEntityFactory {
public:
    explicit BattleStageFactory(const TextureManager& t_manager, WorldRenderer& renderer)
        : textureManager(t_manager), renderer(renderer) {}

    std::unique_ptr<Player> createPlayer() override;
    std::unique_ptr<AIBomber> createAIBomber(float x, float y, BomberType type) override;
    std::unique_ptr<Bomb> createBomb(float x, float y, int blast_radius) override;
    std::unique_ptr<DestructibleWall> createDestructibleWall(float x, float y) override;
    std::unique_ptr<Explosion> createExplosion(float x, float y, ExplosionType type) override;
    std::unique_ptr<CrumblingWall> createCrumblingWall(float x, float y) override;
    std::unique_ptr<PowerUp> createPowerUp(float x, float y) override;
    std::unique_ptr<KnockedOutBomber> createKnockedOutBomber(float x, float y, BomberType type) override;

private:
    template <typename T, typename ViewCreator>
    std::unique_ptr<T> createEntity(std::unique_ptr<T> entity, ViewCreator&& viewCreator) {
        const auto view = viewCreator(entity.get());
        entity->addObserver(view);
        return entity;
    }

    const TextureManager& textureManager;
    WorldRenderer& renderer;
};

#endif // BOMBERMAN_BATTLESTAGEFACTORY_H
