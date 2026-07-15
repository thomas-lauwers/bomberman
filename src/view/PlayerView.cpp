#include "../../include/view/PlayerView.h"
#include "../../include/logic/World.h"
#include "../../include/view/TextureManager.h"
#include "../../include/logic/Camera.h"
#include "../../include/utils/Position.h"
#include "../../include/logic/factory/Entity.h"
#include "../../include/view/Direction.h"

PlayerView::PlayerView(const TextureManager& t_manager) : currentAction{AnimationState::Idle}, currentDirection{Direction::Down} {
    sprite.setTexture(t_manager.getTexture("character_sprites"));
    sprite.setOrigin(0.0f, 12.0f);
    setupAnimations();
}

void PlayerView::setupAnimations() {
    // Movement animations
    animationConfig.addAnimation(AnimationState::Moving, Direction::Down, {
        {sf::IntRect(3, 47, 16, 24), sf::IntRect(20, 47, 16, 24), sf::IntRect(37, 47, 16, 24), sf::IntRect(20, 47, 16, 24)},
        0.2f, true
    });
    animationConfig.addAnimation(AnimationState::Moving, Direction::Up, {
        {sf::IntRect(3, 97, 16, 24), sf::IntRect(20, 97, 16, 24), sf::IntRect(37, 97, 16, 24), sf::IntRect(20, 97, 16, 24)},
        0.2f, true
    });
    animationConfig.addAnimation(AnimationState::Moving, Direction::Left, {
        {sf::IntRect(3, 122, 16, 24), sf::IntRect(20, 122, 16, 24), sf::IntRect(37, 122, 16, 24), sf::IntRect(20, 122, 16, 24)},
        0.2f, true
    });
    animationConfig.addAnimation(AnimationState::Moving, Direction::Right, {
        {sf::IntRect(3, 72, 16, 24), sf::IntRect(20, 72, 16, 24), sf::IntRect(37, 72, 16, 24), sf::IntRect(20, 72, 16, 24)},
        0.2f, true
    });

    // Idle animations
    animationConfig.addAnimation(AnimationState::Idle, Direction::Down, {{sf::IntRect(20, 47, 16, 24)}, 1.0f, false});
    animationConfig.addAnimation(AnimationState::Idle, Direction::Up, {{sf::IntRect(20, 97, 16, 24)}, 1.0f, false});
    animationConfig.addAnimation(AnimationState::Idle, Direction::Left, {{sf::IntRect(20, 122, 16, 24)}, 1.0f, false});
    animationConfig.addAnimation(AnimationState::Idle, Direction::Right, {{sf::IntRect(20, 72, 16, 24)}, 1.0f, false});
}

void PlayerView::draw(sf::RenderWindow& window, const Entity &entity) {
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

void PlayerView::update(const float deltaTime) {
    const Animation& anim = animationConfig.getAnimation(currentAction, currentDirection);

    animationTimer += deltaTime;

    if (animationTimer >= anim.duration && !anim.frames.empty()) {
        animationTimer = 0.0f;

        if (anim.loop || frameIndex < anim.frames.size() - 1) {
            frameIndex = (frameIndex + 1) % anim.frames.size();
        }
    }
}

void PlayerView::onNotify(const Entity& entity, const Event event) {
    AnimationState newAction = currentAction;
    Direction newDirection = currentDirection;

    switch(event) {
        case Event::PlayerMovedUp:
            newAction = AnimationState::Moving;
            newDirection = Direction::Up;
            break;
        case Event::PlayerMovedDown:
            newAction = AnimationState::Moving;
            newDirection = Direction::Down;
            break;
        case Event::PlayerMovedLeft:
            newAction = AnimationState::Moving;
            newDirection = Direction::Left;
            break;
        case Event::PlayerMovedRight:
            newAction = AnimationState::Moving;
            newDirection = Direction::Right;
            break;
        case Event::PlayerStopped:
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
