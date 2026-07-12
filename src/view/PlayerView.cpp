#include "../../include/view/PlayerView.h"
#include "../../include/logic/World.h"
#include "../../include/view/TextureManager.h"
#include "../../include/logic/Camera.h"
#include "../../include/utils/Position.h"
#include "../../include/logic/factory/Entity.h"

PlayerView::PlayerView(const TextureManager& t_manager) {
    sprite.setTexture(t_manager.getTexture("character_sprites"));
    sprite.setTextureRect(sf::IntRect(20, 47, 16, 24));

    // Set the origin to the middle of the sprite so sprite doesn't spill over into tile below
    sprite.setOrigin(0.0f, 12.0f);
}

void PlayerView::draw(sf::RenderWindow& window, const Entity &entity) {
    constexpr float spriteScaleX = (2.0f / World::WIDTH) / 16.0f;
    constexpr float spriteScaleY = (2.0f / World::HEIGHT) / 16.0f;

    Position pos = entity.getPosition();
    NormalizedPosition normPos = Camera::worldToNormalized(pos.x, pos.y);

    sprite.setScale(spriteScaleX, spriteScaleY);
    sprite.setPosition(normPos.x, normPos.y);
    window.draw(sprite);
}

void PlayerView::onNotify(const Entity& entity, Event event) {
}
