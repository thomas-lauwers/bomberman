#include "../../../include/logic/factory/Player.h"
#include "../../../include/logic/factory/PowerUp.h"
#include "../../../include/utils/Stopwatch.h"

Player::Player() = default;

EntityType Player::getEntityType() const { return Player_E; }

void Player::setPosition(const float x, const float y) {
    position.x = x;
    position.y = y;
}

Position Player::getPosition() const { return position; }

void Player::move(const float dx, const float dy) {
    const double deltaTime = Stopwatch::getInstance().getDeltaTime();
    position.x += dx * speed * static_cast<float>(deltaTime);
    position.y += dy * speed * static_cast<float>(deltaTime);

    if (dx != 0 || dy != 0) {
        isMoving = true;
    }
}

void Player::update(const float deltaTime) {
    if (!isMoving && wasMoving) {
        notify(*this, Event::PlayerStopped);
    }
    wasMoving = isMoving;
    isMoving = false;

    if (bomb_cooldown_timer > 0.0f) {
        bomb_cooldown_timer -= deltaTime;
    }
}

Rect Player::getCollisionRect() const { return {position.x + 0.1f, position.y + 0.1f, 0.8f, 0.8f}; }

void Player::onNotify(const Entity& entity, const Event event) {
    if (event == Event::BombExploded) {
        number_of_bombs += 1;
    }
}

bool Player::canPlaceBomb() const {
    if (number_of_bombs > 0 && bomb_cooldown_timer <= 0.0f) {
        return true;
    }
    return false;
}

void Player::placeBomb() {
    number_of_bombs -= 1;
    bomb_cooldown_timer = BOMB_COOLDOWN;
}

int Player::getBlastRadius() const { return blast_radius; }

void Player::gainPowerUp(const PowerUpType type) {
    switch (type) {
    case Fire:
        blast_radius += 1;
        break;
    case ExtraBomb:
        number_of_bombs += 1;
        break;
    case Skates:
        speed += 1;
        break;
    }
}

void Player::triggerEvent(Event event) { notify(*this, event); }
