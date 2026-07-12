#include "../../include/view/DestructibleWallView.h"
#include "../../include/view/TextureManager.h"
#include "../../include/logic/World.h"
#include "../../include/utils/Position.h"
#include "../../include/logic/Camera.h"
#include "../../include/logic/factory/Entity.h"


DestructibleWallView::DestructibleWallView(const TextureManager &t_manager) {
    sprite.setTexture(t_manager.getTexture("battle_stage_sprites"));
    sprite.setTextureRect(sf::IntRect(35, 15, 16, 16));
}

void DestructibleWallView::draw(sf::RenderWindow &window, const Entity &entity) {
    constexpr float spriteScaleX = (2.0f / World::WIDTH) / 16.0f;
    constexpr float spriteScaleY = (2.0f / World::HEIGHT) / 16.0f;

    Position pos = entity.getPosition();
    NormalizedPosition normPos = Camera::worldToNormalized(pos.x, pos.y);

    sprite.setScale(spriteScaleX, spriteScaleY);
    sprite.setPosition(normPos.x, normPos.y);
    window.draw(sprite);
}

void DestructibleWallView::onNotify(const Entity& entity, Event event) {
}
