#include "../../../include/view/entities/PlayerView.h"
#include "../../../include/view/entities/HitboxRenderer.h"
#include <SFML/Graphics.hpp>

PlayerView::PlayerView(const TextureManager& t_manager) : BomberView(t_manager) { setupAnimations(0, 0); }

void PlayerView::draw(sf::RenderWindow& window, const Entity& entity) {
    BomberView::draw(window, entity);
    drawHitbox(window, entity);
}
