#include "../../include/view/WorldRenderer.h"
#include "../../include/logic/Camera.h"
#include "../../include/view/ViewportUtility.h"
#include "../../include/logic/factory/Player.h"

WorldRenderer::WorldRenderer() : p_view{t_manager}, d_wall_view{t_manager}, b_view{t_manager} {
    loadTileSprites();
}

void WorldRenderer::loadTileSprites() {
    wall_sprite.setTexture(t_manager.getTexture("battle_stage_sprites"));
    wall_sprite.setTextureRect(sf::IntRect(18, 15, 16, 16));

    empty_sprite.setTexture(t_manager.getTexture("battle_stage_sprites"));
    empty_sprite.setTextureRect(sf::IntRect(52, 15, 16, 16));

    empty_shaded_sprite.setTexture(t_manager.getTexture("battle_stage_sprites"));
    empty_shaded_sprite.setTextureRect(sf::IntRect(69, 15, 16, 16));
}


void WorldRenderer::render(sf::RenderWindow &window, const World& world) {
    renderTiles(window, world);
    renderEntities(window, world);
    renderPlayer(window, world);
}

void WorldRenderer::renderTiles(sf::RenderWindow &window, const World &world) {
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
                    if (y == 0 || world.getTile(x,y-1).getType() == TileType::W || world.isDestructibleWallAt(x, y-1)) {
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

void WorldRenderer::renderPlayer(sf::RenderWindow &window, const World &world) {
    if (const Player* player = world.getPlayer()) {
        p_view.draw(window, *player);
    }
}

void WorldRenderer::renderEntities(sf::RenderWindow &window, const World &world) {
    for (const auto& entity : world.getEntities()) {
        switch (entity->getEntityType()) {
            case DestructibleWall_E:
                d_wall_view.draw(window, *entity);
                break;

            case Bomb_E:
                b_view.draw(window, *entity);
                break;

            default:
                break;
        }
    }
}
