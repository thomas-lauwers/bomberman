#include "../../include/view/WorldRenderer.h"
#include "../../include/logic/Camera.h"
#include "../../include/util/ViewportUtility.h"

WorldRenderer::WorldRenderer() {
    loadAssets();
}

void WorldRenderer::loadAssets() {
    wall.loadFromFile("assets/tile_sprites.png", sf::IntRect(0, 0, 16, 16));
    wall_sprite.setTexture(wall);

    destructible.loadFromFile("assets/tile_sprites.png", sf::IntRect(16, 0, 16, 16));
    destructible_sprite.setTexture(destructible);

    empty.loadFromFile("assets/tile_sprites.png", sf::IntRect(32, 0, 16, 16));
    empty_sprite.setTexture(empty);

    empty_shaded.loadFromFile("assets/tile_sprites.png", sf::IntRect(48, 0, 16, 16));
    empty_shaded_sprite.setTexture(empty_shaded);
}

void WorldRenderer::render(sf::RenderWindow &window, const World& world) {
    constexpr float worldAspect = static_cast<float>(World::WIDTH) / static_cast<float>(World::HEIGHT);
    ViewportUtility::setViewport(window, worldAspect);

    constexpr float spriteScaleX = (2.0f / World::WIDTH) / 16.0f;
    constexpr float spriteScaleY = (2.0f / World::HEIGHT) / 16.0f;

    for (int y = 0; y < World::HEIGHT; ++y) {
        for (int x = 0; x < World::WIDTH; ++x) {
            const TileType type = world.getTile(x, y);
            sf::Sprite* current_sprite = nullptr;

            switch (type) {
                case TileType::W:
                    current_sprite = &wall_sprite;
                    break;
                case TileType::D:
                    current_sprite = &destructible_sprite;
                    break;
                case TileType::E:
                    if (y == 0 || world.getTile(x,y-1) != TileType::E) {
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
