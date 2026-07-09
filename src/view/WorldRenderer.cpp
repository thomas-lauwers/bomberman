#include "../../include/view/WorldRenderer.h"

WorldRenderer::WorldRenderer() {
    wall.loadFromFile("assets/sprites.png", sf::IntRect(0, 0, 32, 32));
    wall_sprite.setTexture(wall);
}

void WorldRenderer::render(sf::RenderWindow &window, const World& world) {
    window.draw(wall_sprite);
}
