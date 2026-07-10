#include "../../../include/logic/factory/Player.h"

#include "../../../include/utils/Stopwatch.h"

Player::Player() : position{1.0f, 1.0f}, speed{3.0f} {}

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
}

Rect Player::getCollisionRect() const {
    return {position.x + 0.1f, position.y + 0.1f, 0.8f, 0.8f};
}
