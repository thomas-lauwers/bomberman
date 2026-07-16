#include "../../../include/view/entities/KnockedOutBomberView.h"

#include "../../../include/logic/Camera.h"
#include "../../../include/logic/World.h"
#include "../../../include/logic/factory/Entity.h"
#include "../../../include/utils/Position.h"
#include "../../../include/view/core/TextureManager.h"

#include <cmath>

KnockedOutBomberView::KnockedOutBomberView(const TextureManager& t_manager) {
    sprite.setTexture(t_manager.getTexture("character_sprites"));
    sprite.setOrigin(0.0f, 12.0f);

    animation.frames = {sf::IntRect(3, 160, 16, 24),
        sf::IntRect(20, 160, 16, 24),
        sf::IntRect(37, 160, 16, 24),
        sf::IntRect(54, 160, 16, 24),
        sf::IntRect(71, 160, 16, 24),
        sf::IntRect(88, 160, 16, 24),
        sf::IntRect(105, 160, 16, 24),
        sf::IntRect(105, 160, 16, 24),
        sf::IntRect(105, 160, 16, 24),
        sf::IntRect(105, 160, 16, 24),
        sf::IntRect(105, 160, 16, 24)
    };
    animation.duration = 0.18181818181f;
    animation.loop = false;
}

void KnockedOutBomberView::draw(sf::RenderWindow& window, const Entity& entity) {
    constexpr float spriteScaleX = (2.0f / World::WIDTH) / 16.0f;
    constexpr float spriteScaleY = (2.0f / World::HEIGHT) / 16.0f;

    sprite.setTextureRect(animation.frames[frameIndex]);

    Position pos = entity.getPosition();

    // Compute single bounce offset
    float verticalOffset = 0.0f;
    if (bounceTimer < bounceDuration) {
        const float t = bounceTimer / bounceDuration;
        verticalOffset = bounceAmplitude * std::sin(t * 3.14159265f);
    }

    NormalizedPosition normPos = Camera::worldToNormalized(pos.x, pos.y - verticalOffset);
    sprite.setScale(spriteScaleX, spriteScaleY);
    sprite.setPosition(normPos.x, normPos.y);
    window.draw(sprite);
}

void KnockedOutBomberView::update(const float deltaTime) {
    animationTimer += deltaTime;

    if (animationTimer >= animation.duration && !animation.frames.empty() && frameIndex < animation.frames.size() - 1) {
        animationTimer = 0.0f;
        frameIndex++;
    }

    if (bounceTimer < bounceDuration) {
        bounceTimer += deltaTime;
        if (bounceTimer > bounceDuration)
            bounceTimer = bounceDuration;
    }
}

void KnockedOutBomberView::onNotify(const Entity& entity, Event event) {}
