#include "../../../include/view/entities/PowerUpView.h"
#include "../../../include/logic/Camera.h"
#include "../../../include/logic/World.h"
#include "../../../include/logic/factory/Entity.h"
#include "../../../include/logic/factory/PowerUp.h"
#include "../../../include/utils/Position.h"
#include "../../../include/view/core/TextureManager.h"
#include "../../../include/view/entities/HitboxRenderer.h"

namespace {
std::vector<sf::IntRect> getFrames(const PowerUpType type) {
    switch (type) {
    case Fire:
        return {sf::IntRect(16, 0, 16, 16), sf::IntRect(16, 16, 16, 16)};
    case ExtraBomb:
        return {sf::IntRect(0, 0, 16, 16), sf::IntRect(0, 16, 16, 16)};
    case Skates:
        return {sf::IntRect(16, 32, 16, 16), sf::IntRect(16, 48, 16, 16)};
    default:
        return {};
    }
}
} // namespace

PowerUpView::PowerUpView(const TextureManager& t_manager, const PowerUpType type) : type(type) {
    sprite.setTexture(t_manager.getTexture("powerup_sprites"));

    animation.duration = 0.3f;
    animation.loop = true;
    animation.frames = getFrames(type);
}

void PowerUpView::draw(sf::RenderWindow& window, const Entity& entity) {
    constexpr float spriteScaleX = (2.0f / World::WIDTH) / 16.0f;
    constexpr float spriteScaleY = (2.0f / World::HEIGHT) / 16.0f;

    sprite.setTextureRect(animation.frames[frameIndex]);

    Position pos = entity.getPosition();
    NormalizedPosition normPos = Camera::worldToNormalized(pos.x, pos.y);

    sprite.setScale(spriteScaleX, spriteScaleY);
    sprite.setPosition(normPos.x, normPos.y);
    window.draw(sprite);
}

void PowerUpView::update(const float deltaTime) {
    animationTimer += deltaTime;
    if (animationTimer >= animation.duration) {
        animationTimer = 0.0f;
        frameIndex = (frameIndex + 1) % animation.frames.size();
    }
}

void PowerUpView::onNotify(const Entity& entity, const Event event) {}