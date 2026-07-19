#include "../../../include/view/entities/ExplosionView.h"
#include "../../../include/view/entities/HitboxRenderer.h"
#include "../../../include/logic/Camera.h"
#include "../../../include/logic/World.h"
#include "../../../include/logic/factory/Explosion.h"
#include "../../../include/utils/Position.h"
#include "../../../include/view/core/TextureManager.h"

namespace {
std::vector<sf::IntRect> getFrames(const ExplosionType type) {
    switch (type) {
    case ExplosionType::Center:
        return {sf::IntRect(69, 83, 16, 16),  sf::IntRect(120, 66, 16, 16), sf::IntRect(103, 66, 16, 16),
                sf::IntRect(86, 66, 16, 16),  sf::IntRect(69, 66, 16, 16),  sf::IntRect(86, 66, 16, 16),
                sf::IntRect(103, 66, 16, 16), sf::IntRect(120, 66, 16, 16), sf::IntRect(69, 83, 16, 16)};
    case ExplosionType::EndUp:
        return {sf::IntRect(69, 49, 16, 16),  sf::IntRect(86, 49, 16, 16),  sf::IntRect(103, 49, 16, 16),
                sf::IntRect(120, 49, 16, 16), sf::IntRect(120, 32, 16, 16), sf::IntRect(120, 49, 16, 16),
                sf::IntRect(103, 49, 16, 16), sf::IntRect(86, 49, 16, 16),  sf::IntRect(69, 49, 16, 16)};
    case ExplosionType::EndDown:
        return {sf::IntRect(52, 49, 16, 16),   sf::IntRect(69, 100, 16, 16), sf::IntRect(120, 100, 16, 16),
                sf::IntRect(103, 100, 16, 16), sf::IntRect(86, 100, 16, 16), sf::IntRect(103, 100, 16, 16),
                sf::IntRect(120, 100, 16, 16), sf::IntRect(69, 100, 16, 16), sf::IntRect(52, 49, 16, 16)};
    case ExplosionType::EndLeft:
        return {sf::IntRect(1, 32, 16, 16),  sf::IntRect(18, 32, 16, 16), sf::IntRect(35, 32, 16, 16),
                sf::IntRect(52, 32, 16, 16), sf::IntRect(69, 32, 16, 16), sf::IntRect(52, 32, 16, 16),
                sf::IntRect(35, 32, 16, 16), sf::IntRect(18, 32, 16, 16), sf::IntRect(1, 32, 16, 16)};
    case ExplosionType::EndRight:
        return {sf::IntRect(52, 83, 16, 16),  sf::IntRect(52, 66, 16, 16), sf::IntRect(18, 100, 16, 16),
                sf::IntRect(18, 83, 16, 16),  sf::IntRect(18, 66, 16, 16), sf::IntRect(18, 83, 16, 16),
                sf::IntRect(18, 100, 16, 16), sf::IntRect(52, 66, 16, 16), sf::IntRect(52, 83, 16, 16)};
    case ExplosionType::Horizontal:
        return {sf::IntRect(35, 83, 16, 16),  sf::IntRect(35, 66, 16, 16), sf::IntRect(1, 100, 16, 16),
                sf::IntRect(1, 83, 16, 16),  sf::IntRect(1, 66, 16, 16), sf::IntRect(1, 83, 16, 16),
                sf::IntRect(1, 100, 16, 16), sf::IntRect(35, 66, 16, 16), sf::IntRect(35, 83, 16, 16)};
    case ExplosionType::Vertical:
        return {sf::IntRect(52, 100, 16, 16),  sf::IntRect(35, 100, 16, 16), sf::IntRect(120, 83, 16, 16),
                sf::IntRect(103, 83, 16, 16),  sf::IntRect(86, 83, 16, 16), sf::IntRect(103, 83, 16, 16),
                sf::IntRect(120, 83, 16, 16), sf::IntRect(35, 100, 16, 16), sf::IntRect(52, 100, 16, 16)};
    default:
        return {};
    }
}
} // namespace

ExplosionView::ExplosionView(const TextureManager& t_manager, const ExplosionType type) : type(type) {
    sprite.setTexture(t_manager.getTexture("battle_stage_sprites"));

    animation.duration = 0.05555555555f;
    animation.loop = false;
    animation.frames = getFrames(type);
}

void ExplosionView::draw(sf::RenderWindow& window, const Entity& entity) {
    constexpr float spriteScaleX = (2.0f / World::WIDTH) / 16.0f;
    constexpr float spriteScaleY = (2.0f / World::HEIGHT) / 16.0f;

    sprite.setTextureRect(animation.frames[frameIndex]);

    Position pos = entity.getPosition();
    NormalizedPosition normPos = Camera::worldToNormalized(pos.x, pos.y);

    sprite.setScale(spriteScaleX, spriteScaleY);
    sprite.setPosition(normPos.x, normPos.y);
    window.draw(sprite);
    drawHitbox(window, entity);
}

void ExplosionView::onNotify(const Entity& entity, Event event) {}

void ExplosionView::update(const float deltaTime) {
    animationTimer += deltaTime;

    if (animationTimer >= animation.duration && !animation.frames.empty() && frameIndex < animation.frames.size() - 1) {
        animationTimer = 0.0f;
        frameIndex++;
    }
}
