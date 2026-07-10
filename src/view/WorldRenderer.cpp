#include "../../include/view/WorldRenderer.h"
#include "../../include/logic/Camera.h"
#include "../../include/utils/ViewportUtility.h"
#include "../../include/logic/factory/Player.h"

WorldRenderer::WorldRenderer() {
    loadAssets();
}

void WorldRenderer::loadAssets() {
    wall.loadFromFile("assets/battle_stage_sprites.png", sf::IntRect(18, 15, 16, 16));
    wall_sprite.setTexture(wall);

    destructible.loadFromFile("assets/battle_stage_sprites.png", sf::IntRect(35, 15, 16, 16));
    destructible_sprite.setTexture(destructible);

    empty.loadFromFile("assets/battle_stage_sprites.png", sf::IntRect(52, 15, 16, 16));
    empty_sprite.setTexture(empty);

    empty_shaded.loadFromFile("assets/battle_stage_sprites.png", sf::IntRect(69, 15, 16, 16));
    empty_shaded_sprite.setTexture(empty_shaded);

    player.loadFromFile("assets/character_sprites.png", sf::IntRect(20, 47, 16, 24));
    player_sprite.setTexture(player);

    // Set the origin to the middle of the sprite so sprite doesn't spill over into tile below
    player_sprite.setOrigin(0.0f, 12.0f);
}

void WorldRenderer::render(sf::RenderWindow &window, const World& world) {
    renderTiles(window, world);
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
                case TileType::D:
                    current_sprite = &destructible_sprite;
                    break;
                case TileType::E:
                    if (y == 0 || world.getTile(x,y-1).getType() != TileType::E) {
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
    constexpr float spriteScaleX = (2.0f / World::WIDTH) / 16.0f;
    constexpr float spriteScaleY = (2.0f / World::HEIGHT) / 16.0f;

    auto* player = world.getPlayer();

    if (player) {
        Position pos = player->getPosition();
        NormalizedPosition normPos = Camera::worldToNormalized(pos.x, pos.y);

        player_sprite.setScale(spriteScaleX, spriteScaleY);
        player_sprite.setPosition(normPos.x, normPos.y);
        window.draw(player_sprite);
    }
}
