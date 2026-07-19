#include "../../../include/view/entities/BomberView.h"
#include "../../../include/view/entities/HitboxRenderer.h"
#include "../../../include/logic/Camera.h"
#include "../../../include/logic/World.h"
#include "../../../include/logic/factory/Entity.h"
#include "../../../include/utils/Position.h"
#include "../../../include/view/Direction.h"
#include "../../../include/view/core/TextureManager.h"

BomberView::BomberView(const TextureManager& t_manager)
    : currentAction{AnimationState::Idle}, currentDirection{Direction::Down} {
    sprite.setTexture(t_manager.getTexture("character_sprites"));
    sprite.setOrigin(8.0f, 17.0f);
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
    drawHitbox(window, entity);
    drawPosition(window, entity);
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

void BomberView::setupAnimations(const int xOffset, const int yOffset) {
    // Movement animations
    animationConfig.addAnimation(AnimationState::Moving, Direction::Down,
                                 {{sf::IntRect(3 + xOffset, 47 + yOffset, 16, 24), sf::IntRect(20 + xOffset, 47 + yOffset, 16, 24), sf::IntRect(37 + xOffset, 47 + yOffset, 16, 24),
                                   sf::IntRect(20 + xOffset, 47 + yOffset, 16, 24)},
                                  0.2f,
                                  true});
    animationConfig.addAnimation(AnimationState::Moving, Direction::Up,
                                 {{sf::IntRect(3 + xOffset, 97 + yOffset, 16, 24), sf::IntRect(20 + xOffset, 97 + yOffset, 16, 24), sf::IntRect(37 + xOffset, 97 + yOffset, 16, 24),
                                   sf::IntRect(20 + xOffset, 97 + yOffset, 16, 24)},
                                  0.2f,
                                  true});
    animationConfig.addAnimation(AnimationState::Moving, Direction::Left,
                                 {{sf::IntRect(3 + xOffset, 122 + yOffset, 16, 24), sf::IntRect(20 + xOffset, 122 + yOffset, 16, 24),
                                   sf::IntRect(37 + xOffset, 122 + yOffset, 16, 24), sf::IntRect(20 + xOffset, 122 + yOffset, 16, 24)},
                                  0.2f,
                                  true});
    animationConfig.addAnimation(AnimationState::Moving, Direction::Right,
                                 {{sf::IntRect(3 + xOffset, 72 + yOffset, 16, 24), sf::IntRect(20 + xOffset, 72 + yOffset, 16, 24), sf::IntRect(37 + xOffset, 72 + yOffset, 16, 24),
                                   sf::IntRect(20 + xOffset, 72 + yOffset, 16, 24)},
                                  0.2f,
                                  true});

    // Idle animations
    animationConfig.addAnimation(AnimationState::Idle, Direction::Down, {{sf::IntRect(20 + xOffset, 47 + yOffset, 16, 24)}, 1.0f, false});
    animationConfig.addAnimation(AnimationState::Idle, Direction::Up, {{sf::IntRect(20 + xOffset, 97 + yOffset, 16, 24)}, 1.0f, false});
    animationConfig.addAnimation(AnimationState::Idle, Direction::Left, {{sf::IntRect(20 + xOffset, 122 + yOffset, 16, 24)}, 1.0f, false});
    animationConfig.addAnimation(AnimationState::Idle, Direction::Right, {{sf::IntRect(20 + xOffset, 72 + yOffset, 16, 24)}, 1.0f, false});
}
