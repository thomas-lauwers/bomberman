#include "../../include/view/WorldRenderer.h"

WorldRenderer::WorldRenderer() {
    loadAssets();
}

void WorldRenderer::loadAssets() {
    wall.loadFromFile("assets/tile_sprites.png", sf::IntRect(0, 0, 16, 16));
    wall_sprite.setTexture(wall);
    wall_sprite.setScale(2.f, 2.f);

    destructible.loadFromFile("assets/tile_sprites.png", sf::IntRect(17, 0, 16, 16));
    destructible_sprite.setTexture(destructible);
    destructible_sprite.setScale(2.f, 2.f);

    empty.loadFromFile("assets/tile_sprites.png", sf::IntRect(33, 0, 16, 16));
    empty_sprite.setTexture(empty);
    empty_sprite.setScale(2.f, 2.f);
}

void WorldRenderer::render(sf::RenderWindow &window, const World& world) const {
    window.draw(wall_sprite);
}
