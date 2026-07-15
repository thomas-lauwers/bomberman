#include "../../../include/logic/factory/Player.h"
#include "../../../include/utils/Stopwatch.h"

Player::Player() = default;

EntityType Player::getEntityType() const {
    return Player_E;
}

void Player::setPosition(const float x, const float y) {
    position.x = x;
    position.y = y;
}

Position Player::getPosition() const {
    return position;
}

void Player::move(const float dx, const float dy) {
    const double deltaTime = Stopwatch::getInstance().getDeltaTime();
    position.x += dx * speed * static_cast<float>(deltaTime);
    position.y += dy * speed * static_cast<float>(deltaTime);

    if (dx != 0 || dy != 0) {
        isMoving = true;
    }
}

void Player::update(float deltaTime) {
    if (!isMoving && wasMoving) {
        notify(*this, Event::PlayerStopped);
    }
    wasMoving = isMoving;
    isMoving = false;
}

Rect Player::getCollisionRect() const {
    return {position.x + 0.1f, position.y + 0.1f, 0.8f, 0.8f};
}

void Player::onNotify(const Entity& entity, const Event event) {
    if (event == Event::EntityDestroyed && entity.getEntityType() == Bomb_E) {
        canPlace = true;
    }
}

bool Player::canPlaceBomb() const {
    return canPlace;
}

void Player::setCanPlaceBomb(const bool can) {
    canPlace = can;
}

void Player::triggerEvent(Event event) {
    notify(*this, event);
}
