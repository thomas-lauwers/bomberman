#include "../../include/view/PlayerView.h"
#include "../../include/logic/World.h"
#include "../../include/view/TextureManager.h"
#include "../../include/logic/Camera.h"
#include "../../include/utils/Position.h"
#include "../../include/logic/factory/Entity.h"
#include "../../include/view/Direction.h"

PlayerView::PlayerView(const TextureManager& t_manager) : currentAction{AnimationState::Idle}, currentDirection{Direction::Down} {
    sprite.setTexture(t_manager.getTexture("character_sprites"));

    // Set the origin to the middle of the sprite so sprite doesn't spill over into tile below
    sprite.setOrigin(0.0f, 12.0f);

    // Movement animations
    Animation moveDown;
    moveDown.frames = {
        sf::IntRect(3, 47, 16, 24),
        sf::IntRect(20, 47, 16, 24),
        sf::IntRect(37, 47, 16, 24),
        sf::IntRect(20, 47, 16, 24)
    };
    moveDown.duration = 0.2f;
    moveDown.loop = true;
    animationConfig.addAnimation(AnimationState::Moving, Direction::Down, moveDown);

    Animation moveUp;
    moveUp.frames = {
        sf::IntRect(3, 97, 16, 24),
        sf::IntRect(20, 97, 16, 24),
        sf::IntRect(37, 97, 16, 24),
        sf::IntRect(20, 97, 16, 24)
    };
    moveUp.duration = 0.2f;
    moveUp.loop = true;
    animationConfig.addAnimation(AnimationState::Moving, Direction::Up, moveUp);

    Animation moveLeft;
    moveLeft.frames = {
        sf::IntRect(3, 122, 16, 24),
        sf::IntRect(20, 122, 16, 24),
        sf::IntRect(37, 122, 16, 24),
        sf::IntRect(20, 122, 16, 24)
    };
    moveLeft.duration = 0.2f;
    moveLeft.loop = true;
    animationConfig.addAnimation(AnimationState::Moving, Direction::Left, moveLeft);

    Animation moveRight;
    moveRight.frames = {
        sf::IntRect(3, 72, 16, 24),
        sf::IntRect(20, 72, 16, 24),
        sf::IntRect(37, 72, 16, 24),
        sf::IntRect(20, 72, 16, 24)
    };
    moveRight.duration = 0.2f;
    moveRight.loop = true;
    animationConfig.addAnimation(AnimationState::Moving, Direction::Right, moveRight);

    // Idle animations
    Animation idleDown;
    idleDown.frames = {
        sf::IntRect(20, 47, 16, 24),
    };
    idleDown.duration = 1.0f;
    idleDown.loop = false;
    animationConfig.addAnimation(AnimationState::Idle, Direction::Down, idleDown);

    Animation idleUp;
    idleUp.frames = {
        sf::IntRect(20, 97, 16, 24),
    };
    idleUp.duration = 1.0f;
    idleUp.loop = false;
    animationConfig.addAnimation(AnimationState::Idle, Direction::Up, idleUp);

    Animation idleLeft;
    idleLeft.frames = {
        sf::IntRect(20, 122, 16, 24),
    };
    idleLeft.duration = 1.0f;
    idleLeft.loop = false;
    animationConfig.addAnimation(AnimationState::Idle, Direction::Left, idleLeft);

    Animation idleRight;
    idleRight.frames = {
        sf::IntRect(20, 72, 16, 24),
    };
    idleRight.duration = 1.0f;
    idleRight.loop = false;
    animationConfig.addAnimation(AnimationState::Idle, Direction::Right, idleRight);
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

    if (animationTimer >= anim.duration) {
        animationTimer = 0.0f;

        // Advance frame only if we are not at the end of a non-looping animation
        if (anim.loop || frameIndex < static_cast<int>(anim.frames.size()) - 1) {
            frameIndex++;
            if (frameIndex >= static_cast<int>(anim.frames.size())) {
                frameIndex = 0;
            }
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
