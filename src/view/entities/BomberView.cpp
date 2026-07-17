#include "../../../include/view/entities/BomberView.h"
#include "../../../include/logic/Camera.h"
#include "../../../include/logic/World.h"
#include "../../../include/logic/factory/Entity.h"
#include "../../../include/utils/Position.h"
#include "../../../include/view/Direction.h"
#include "../../../include/view/core/TextureManager.h"

BomberView::BomberView(const TextureManager& t_manager)
    : currentAction{AnimationState::Idle}, currentDirection{Direction::Down} {
    sprite.setTexture(t_manager.getTexture("character_sprites"));
    sprite.setOrigin(0.0f, 12.0f);
}

void BomberView::draw(sf::RenderWindow& window, const Entity& entity) {
    const Animation& anim = animationConfig.getAnimation(currentAction, currentDirection);
    sprite.setTextureRect(anim.frames[frameIndex]);

    constexpr float spriteScaleX = (2.0f / World::WIDTH) / 16.0f;
    constexpr float spriteScaleY = (2.0f / World::HEIGHT) / 16.0f;

    Position pos = entity.getPosition();
    NormalizedPosition normPos = Camera::worldToNormalized(pos.x, pos.y);

    sprite.setScale(spriteScaleX, spriteScaleY);
    sprite.setPosition(normPos.x, normPos.y);
    window.draw(sprite);
}

void BomberView::update(const float deltaTime) {
    const Animation& anim = animationConfig.getAnimation(currentAction, currentDirection);

    animationTimer += deltaTime;

    if (animationTimer >= anim.duration && !anim.frames.empty()) {
        animationTimer = 0.0f;

        if (anim.loop || frameIndex < anim.frames.size() - 1) {
            frameIndex = (frameIndex + 1) % anim.frames.size();
        }
    }
}

void BomberView::onNotify(const Entity& entity, const Event event) {
    AnimationState newAction = currentAction;
    Direction newDirection = currentDirection;

    switch (event) {
    case Event::BomberMovedUp:
        newAction = AnimationState::Moving;
        newDirection = Direction::Up;
        break;
    case Event::BomberMovedDown:
        newAction = AnimationState::Moving;
        newDirection = Direction::Down;
        break;
    case Event::BomberMovedLeft:
        newAction = AnimationState::Moving;
        newDirection = Direction::Left;
        break;
    case Event::BomberMovedRight:
        newAction = AnimationState::Moving;
        newDirection = Direction::Right;
        break;
    case Event::BomberStopped:
        newAction = AnimationState::Idle;
        break;
    default:
        break;
    }

    if (newAction != currentAction || newDirection != currentDirection) {
        currentAction = newAction;
        currentDirection = newDirection;
        frameIndex = 0;
        animationTimer = 0.0f;
    }
}
