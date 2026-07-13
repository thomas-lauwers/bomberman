#include "../../include/view/ExplosionView.h"
#include "../../include/logic/factory/Explosion.h"
#include "../../include/view/TextureManager.h"
#include "../../include/logic/Camera.h"
#include "../../include/utils/Position.h"
#include "../../include/logic/World.h"

ExplosionView::ExplosionView(const TextureManager &t_manager) {
    sprite.setTexture(t_manager.getTexture("battle_stage_sprites"));
    sprite.setTextureRect(sf::IntRect(69, 83, 16, 16));
}

void ExplosionView::draw(sf::RenderWindow &window, const Entity &entity) {
    constexpr float spriteScaleX = (2.0f / World::WIDTH) / 16.0f;
    constexpr float spriteScaleY = (2.0f / World::HEIGHT) / 16.0f;

    switch (const auto& explosion = static_cast<const Explosion&>(entity); explosion.getType()) {
        case ExplosionType::Center: sprite.setTextureRect(sf::IntRect(69, 83, 16, 16));
            break;
        case ExplosionType::EndUp: sprite.setTextureRect(sf::IntRect(69, 49, 16, 16));
            break;
        case ExplosionType::EndDown: sprite.setTextureRect(sf::IntRect(69, 100, 16, 16));
            break;
        case ExplosionType::EndLeft: sprite.setTextureRect(sf::IntRect(1, 32, 16, 16));
            break;
        case ExplosionType::EndRight: sprite.setTextureRect(sf::IntRect(52, 83, 16, 16));
            break;
        default:
            break;
    }

    Position pos = entity.getPosition();
    NormalizedPosition normPos = Camera::worldToNormalized(pos.x, pos.y);

    sprite.setScale(spriteScaleX, spriteScaleY);
    sprite.setPosition(normPos.x, normPos.y);
    window.draw(sprite);
}

void ExplosionView::onNotify(const Entity& entity, Event event) {
}
