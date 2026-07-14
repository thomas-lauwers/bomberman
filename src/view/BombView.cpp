#include "../../include/view/BombView.h"
#include "../../include/logic/World.h"
#include "../../include/view/TextureManager.h"
#include "../../include/logic/Camera.h"
#include "../../include/utils/Position.h"
#include "../../include/logic/factory/Entity.h"
#include "../../include/view/Animation.h"

BombView::BombView(const TextureManager &t_manager) {
    sprite.setTexture(t_manager.getTexture("battle_stage_sprites"));
    sprite.setTextureRect(sf::IntRect(120, 117, 16, 16));

    bombTicking.frames = {
        sf::IntRect(103, 117, 16, 16),
        sf::IntRect(120, 117, 16, 16),
        sf::IntRect(137, 117, 16, 16),
        sf::IntRect(120, 117, 16, 16),
    };
    bombTicking.duration = 0.3f;
    bombTicking.loop = true;
}

void BombView::draw(sf::RenderWindow &window, const Entity &entity) {
    sprite.setTextureRect(bombTicking.frames[frameIndex]);

    constexpr float spriteScaleX = (2.0f / World::WIDTH) / 16.0f;
    constexpr float spriteScaleY = (2.0f / World::HEIGHT) / 16.0f;

    Position pos = entity.getPosition();
    NormalizedPosition normPos = Camera::worldToNormalized(pos.x, pos.y);

    sprite.setScale(spriteScaleX, spriteScaleY);
    sprite.setPosition(normPos.x, normPos.y);
    window.draw(sprite);
}

void BombView::onNotify(const Entity& entity, Event event) {
}

void BombView::update(const float deltaTime) {
    animationTimer += deltaTime;

    if (animationTimer >= bombTicking.duration) {
        animationTimer = 0.0f;

        // Advance frame only if we are not at the end of a non-looping animation
        if (bombTicking.loop || frameIndex < static_cast<int>(bombTicking.frames.size()) - 1) {
            frameIndex++;
            if (frameIndex >= static_cast<int>(bombTicking.frames.size())) {
                frameIndex = 0;
            }
        }
    }
}
