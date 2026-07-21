#include "../../../include/view/core/WorldRenderer.h"
#include "../../../include/view/core/TitleRenderer.h"
#include "../../../include/logic/Camera.h"
#include "../../../include/logic/World.h"
#include "../../../include/logic/factory/Explosion.h"
#include "../../../include/logic/factory/KnockedOutBomber.h"
#include "../../../include/logic/factory/Player.h"
#include "../../../include/logic/factory/PowerUp.h"
#include <algorithm>
#include <unordered_set>
#include <vector>

WorldRenderer::WorldRenderer(TextureManager& manager, sf::RenderWindow& window)
    : t_manager(manager), window(window), p_view(std::make_shared<PlayerView>(manager)), d_wall_view(manager) {
    loadTileSprites();
    t_manager.loadFont("arcade", "assets/arcadeclassic.ttf");
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

void WorldRenderer::render(const World& world) {
    removeDestroyedEntities(world);

    renderTiles(world);
    renderNonBomberEntities(world);
    renderBombersSorted(world);
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
    for (auto& pair : knockedoutbomberViews) {
        pair.second->update(deltaTime);
    }
    for (auto& pair : aiBomberViews) {
        pair.second->update(deltaTime);
    }
}

void WorldRenderer::renderTiles(const World& world) {
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

void WorldRenderer::renderNonBomberEntities(const World& world) {
    for (const auto& entity : world.getEntities()) {
        switch (entity->getEntityType()) {
        case DestructibleWall_E:
            d_wall_view.draw(window, *entity);
            break;

        case Bomb_E:
            bombViews[entity.get()]->draw(window, *entity);
            break;

        case Explosion_E:
            explosionViews[entity.get()]->draw(window, *entity);
            break;

        case CrumblingWall_E:
            c_wallViews[entity.get()]->draw(window, *entity);
            break;

        case PowerUp_E:
            powerupViews[entity.get()]->draw(window, *entity);
            break;

        case KnockedOutBomber_E:
            knockedoutbomberViews[entity.get()]->draw(window, *entity);
            break;

        default:
            break;
        }
    }
}

void WorldRenderer::renderBombersSorted(const World& world) {
    struct BomberViewPair {
        const Entity* entity;
        IEntityView* view;
    };
    std::vector<BomberViewPair> bombers;

    // Add player
    if (const auto player = world.getPlayer()) {
        bombers.push_back({player.get(), p_view.get()});
    }

    // Add AI bombers
    for (const auto& entity : world.getEntities()) {
        if (entity->getEntityType() == AIBomber_E) {
            bombers.push_back({entity.get(), aiBomberViews[entity.get()].get()});
        }
    }

    // Sort by Y position
    std::sort(bombers.begin(), bombers.end(), [](const BomberViewPair& a, const BomberViewPair& b) {
        return a.entity->getPosition().y < b.entity->getPosition().y;
    });

    // Draw
    for (const auto& pair : bombers) {
        pair.view->draw(window, *pair.entity);
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
    cleanup(knockedoutbomberViews);
    cleanup(aiBomberViews);
}

std::shared_ptr<BombView> WorldRenderer::createBombView(const Entity* entity) {
    auto view = std::make_shared<BombView>(t_manager);
    bombViews[entity] = view;
    return view;
}

std::shared_ptr<ExplosionView> WorldRenderer::createExplosionView(const Entity* entity) {
    const auto explosion = static_cast<const Explosion*>(entity);
    auto view = std::make_shared<ExplosionView>(t_manager, explosion->getType());
    explosionViews[entity] = view;
    return view;
}

std::shared_ptr<CrumblingWallView> WorldRenderer::createCrumblingWallView(const Entity* entity) {
    auto view = std::make_shared<CrumblingWallView>(t_manager);
    c_wallViews[entity] = view;
    return view;
}

std::shared_ptr<PowerUpView> WorldRenderer::createPowerUpView(const Entity* entity) {
    const auto powerup = static_cast<const PowerUp*>(entity);
    auto view = std::make_shared<PowerUpView>(t_manager, powerup->getType());
    powerupViews[entity] = view;
    return view;
}

std::shared_ptr<KnockedOutBomberView> WorldRenderer::createKnockedOutBomberView(const Entity* entity, BomberType type) {
    auto view = std::make_shared<KnockedOutBomberView>(t_manager, type);
    knockedoutbomberViews[entity] = view;
    return view;
}

std::shared_ptr<AIBomberView> WorldRenderer::createAIBomberView(const Entity* entity, BomberType type) {
    auto view = std::make_shared<AIBomberView>(t_manager, type);
    aiBomberViews[entity] = view;
    return view;
}

sf::View WorldRenderer::setupUIView() const {
    const sf::View oldView = window.getView();
    sf::View uiView;
    uiView.setViewport(oldView.getViewport());
    uiView.setSize(720.0f, 624.0f);
    uiView.setCenter(720.0f / 2.0f, 624.0f / 2.0f);
    window.setView(uiView);
    return oldView;
}

void WorldRenderer::renderCenteredText(const std::string& text, const float y) {
    const sf::View oldView = setupUIView();

    sf::Text renderableText;
    renderableText.setFont(t_manager.getFont("arcade"));
    renderableText.setString(text);
    renderableText.setOutlineColor(sf::Color::Black);
    renderableText.setOutlineThickness(2.5f);
    renderableText.setCharacterSize(40);
    renderableText.setFillColor(sf::Color::White);

    // Calculate center based on bounding box
    const sf::FloatRect textRect = renderableText.getLocalBounds();
    renderableText.setOrigin(textRect.left + textRect.width / 2.0f, 
                             textRect.top + textRect.height / 2.0f);
    
    // Position at screen center horizontally
    renderableText.setPosition(720.0f / 2.0f, y);

    window.draw(renderableText);
    window.setView(oldView);
}

void WorldRenderer::renderText(const std::string& text, const float x, const float y) {
    const sf::View oldView = setupUIView();
    
    sf::Text renderableText;
    renderableText.setFont(t_manager.getFont("arcade"));
    renderableText.setString(text);
    renderableText.setOutlineColor(sf::Color::Black);
    renderableText.setOutlineThickness(2.5f);
    renderableText.setCharacterSize(24);
    renderableText.setFillColor(sf::Color::White);
    renderableText.setPosition(x, y);
    
    window.draw(renderableText);
    
    window.setView(oldView);
}

void WorldRenderer::renderPortrait(float x, float y) {
    const sf::View oldView = setupUIView();
    
    sf::Sprite sprite;
    sprite.setTexture(t_manager.getTexture("portrait"));
    sprite.scale(4.0f, 4.0f);
    sprite.setPosition({x, y});
    
    window.draw(sprite);
    
    window.setView(oldView);
}

void WorldRenderer::renderTitle(const bool showEnter) {
    TitleRenderer::render(*this, showEnter);
}
