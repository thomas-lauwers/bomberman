#include "../../include/view/WorldRenderer.h"

#include <memory>

WorldRenderer::WorldRenderer() {
    loadAssets();
}

void WorldRenderer::loadAssets() {
    constexpr float scale = 3.f;

    wall.loadFromFile("assets/tile_sprites.png", sf::IntRect(0, 0, 16, 16));
    wall_sprite.setTexture(wall);
    wall_sprite.setScale(scale, scale);

    destructible.loadFromFile("assets/tile_sprites.png", sf::IntRect(16, 0, 16, 16));
    destructible_sprite.setTexture(destructible);
    destructible_sprite.setScale(scale, scale);

    empty.loadFromFile("assets/tile_sprites.png", sf::IntRect(32, 0, 16, 16));
    empty_sprite.setTexture(empty);
    empty_sprite.setScale(scale, scale);
}

void WorldRenderer::render(sf::RenderWindow &window, const World& world) {
    for (int y = 0; y < World::HEIGHT; ++y) {
        for (int x = 0; x < World::WIDTH; ++x) {
            const TileType type = world.getTile(x, y);
            sf::Sprite* current_sprite = nullptr;

            switch (type) {
                case TileType::W: current_sprite = &wall_sprite; break;
                case TileType::D: current_sprite = &destructible_sprite; break;
                case TileType::E: current_sprite = &empty_sprite; break;
            }

            if (current_sprite) {
                constexpr float TILE_SIZE = 48.f;
                current_sprite->setPosition(static_cast<float>(x) * TILE_SIZE, static_cast<float>(y) * TILE_SIZE);
                window.draw(*current_sprite);
            }
        }
    }
}
