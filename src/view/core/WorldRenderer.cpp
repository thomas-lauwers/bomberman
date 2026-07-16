#include "../../../include/view/core/WorldRenderer.h"
#include "../../../include/logic/Camera.h"
#include "../../../include/logic/World.h"
#include "../../../include/logic/factory/Player.h"
#include <unordered_set>

WorldRenderer::WorldRenderer(TextureManager& manager)
    : t_manager(manager), p_view(std::make_shared<PlayerView>(manager)), d_wall_view(manager) {
    loadTileSprites();
}

std::shared_ptr<PlayerView> WorldRenderer::getPlayerView() const { return p_view; }

void WorldRenderer::loadTileSprites() {
    wall_sprite.setTexture(t_manager.getTexture("battle_stage_sprites"));
    wall_sprite.setTextureRect(sf::IntRect(18, 15, 16, 16));

    empty_sprite.setTexture(t_manager.getTexture("battle_stage_sprites"));
    empty_sprite.setTextureRect(sf::IntRect(52, 15, 16, 16));

    empty_shaded_sprite.setTexture(t_manager.getTexture("battle_stage_sprites"));
    empty_shaded_sprite.setTextureRect(sf::IntRect(69, 15, 16, 16));
}

void WorldRenderer::render(sf::RenderWindow& window, const World& world) {
    removeDestroyedEntities(world);

    renderTiles(window, world);
    renderEntities(window, world);
    renderPlayer(window, world);
}

void WorldRenderer::update(const float deltaTime) {
    p_view->update(deltaTime);
    d_wall_view.update(deltaTime);
    for (auto& pair : bombViews) {
        pair.second->update(deltaTime);
    }
    for (auto& pair : explosionViews) {
        pair.second->update(deltaTime);
    }
    for (auto& pair : c_wallViews) {
        pair.second->update(deltaTime);
    }
    for (auto& pair : powerupViews) {
        pair.second->update(deltaTime);
    }
}

void WorldRenderer::renderTiles(sf::RenderWindow& window, const World& world) {
    constexpr float spriteScaleX = (2.0f / World::WIDTH) / 16.0f;
    constexpr float spriteScaleY = (2.0f / World::HEIGHT) / 16.0f;

    for (int y = 0; y < World::HEIGHT; ++y) {
        for (int x = 0; x < World::WIDTH; ++x) {
            const Tile tile = world.getTile(x, y);
            sf::Sprite* current_sprite = nullptr;

            switch (tile.getType()) {
            case TileType::W:
                current_sprite = &wall_sprite;
                break;

            case TileType::E:
                if (y == 0 || world.getTile(x, y - 1).getType() == TileType::W ||
                    world.isDestructibleWallAt(x, y - 1)) {
                    current_sprite = &empty_shaded_sprite;
                } else {
                    current_sprite = &empty_sprite;
                }
                break;

            default:
                break;
            }

            if (current_sprite) {
                current_sprite->setScale(spriteScaleX, spriteScaleY);
                NormalizedPosition normPos = Camera::gridToNormalized(x, y);
                current_sprite->setPosition(normPos.x, normPos.y);
                window.draw(*current_sprite);
            }
        }
    }
}

void WorldRenderer::renderPlayer(sf::RenderWindow& window, const World& world) const {
    if (const auto player = world.getPlayer()) {
        p_view->draw(window, *player);
    }
}

void WorldRenderer::renderEntities(sf::RenderWindow& window, const World& world) {
    for (const auto& entity : world.getEntities()) {
        switch (entity->getEntityType()) {
        case DestructibleWall_E:
            d_wall_view.draw(window, *entity);
            break;

        case Bomb_E:
            if (bombViews.find(entity.get()) == bombViews.end()) {
                bombViews[entity.get()] = std::make_unique<BombView>(t_manager);
            }
            bombViews[entity.get()]->draw(window, *entity);
            break;

        case Explosion_E:
            if (explosionViews.find(entity.get()) == explosionViews.end()) {
                auto explosion = static_cast<const Explosion*>(entity.get());
                explosionViews[entity.get()] = std::make_unique<ExplosionView>(t_manager, explosion->getType());
            }
            explosionViews[entity.get()]->draw(window, *entity);
            break;

        case CrumblingWall_E:
            if (c_wallViews.find(entity.get()) == c_wallViews.end()) {
                c_wallViews[entity.get()] = std::make_unique<CrumblingWallView>(t_manager);
            }
            c_wallViews[entity.get()]->draw(window, *entity);
            break;

        case PowerUp_E:
            if (powerupViews.find(entity.get()) == powerupViews.end()) {
                auto powerup = static_cast<const PowerUp*>(entity.get());
                powerupViews[entity.get()] = std::make_unique<PowerUpView>(t_manager, powerup->getType());
            }
            powerupViews[entity.get()]->draw(window, *entity);
            break;

        default:
            break;
        }
    }
}

void WorldRenderer::removeDestroyedEntities(const World& world) {
    std::unordered_set<const Entity*> activeEntities;
    for (const auto& entity : world.getEntities()) {
        activeEntities.insert(entity.get());
    }

    // Lambda to encapsulate the cleanup logic
    auto cleanup = [&](auto& viewMap) {
        for (auto it = viewMap.begin(); it != viewMap.end();) {
            // Check if entity is no longer in the world (activeEntities) or destroyed
            if (activeEntities.find(it->first) == activeEntities.end() || it->first->isDestroyed()) {
                it = viewMap.erase(it);
            } else {
                ++it;
            }
        }
    };

    // Apply the cleanup to all view containers
    cleanup(bombViews);
    cleanup(explosionViews);
    cleanup(c_wallViews);
    cleanup(powerupViews);
}
