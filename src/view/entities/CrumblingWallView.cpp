#include "../../../include/view/entities/CrumblingWallView.h"
#include "../../../include/logic/Camera.h"
#include "../../../include/logic/World.h"
#include "../../../include/logic/factory/Entity.h"
#include "../../../include/utils/Position.h"
#include "../../../include/view/core/TextureManager.h"

CrumblingWallView::CrumblingWallView(const TextureManager& t_manager) {
    sprite.setTexture(t_manager.getTexture("battle_stage_sprites"));
    sprite.setTextureRect(sf::IntRect(35, 15, 16, 16));

    animation.frames = {sf::IntRect(1, 117, 16, 16),  sf::IntRect(18, 117, 16, 16), sf::IntRect(35, 117, 16, 16),
                        sf::IntRect(52, 117, 16, 16), sf::IntRect(69, 117, 16, 16), sf::IntRect(86, 117, 16, 16)};
    animation.duration = 0.125f;
    animation.loop = false;
}

void CrumblingWallView::draw(sf::RenderWindow& window, const Entity& entity) {
    constexpr float spriteScaleX = (2.0f / World::WIDTH) / 16.0f;
    constexpr float spriteScaleY = (2.0f / World::HEIGHT) / 16.0f;

    sprite.setTextureRect(animation.frames[frameIndex]);

    Position pos = entity.getPosition();
    NormalizedPosition normPos = Camera::worldToNormalized(pos.x, pos.y);

    sprite.setScale(spriteScaleX, spriteScaleY);
    sprite.setPosition(normPos.x, normPos.y);
    window.draw(sprite);
}

void CrumblingWallView::update(const float deltaTime) {
    animationTimer += deltaTime;

    if (animationTimer >= animation.duration && !animation.frames.empty() && frameIndex < animation.frames.size() - 1) {
        animationTimer = 0.0f;
        frameIndex++;
    }
}

void CrumblingWallView::onNotify(const Entity& entity, Event event) {}
