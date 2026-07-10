#include "../../../include/logic/factory/Player.h"

Player::Player() : position{1.0f, 1.0f} {}

void Player::setPosition(const float x, const float y) {
    position.x = x;
    position.y = y;
}

Position Player::getPosition() const {
    return position;
}
