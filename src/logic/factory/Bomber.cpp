#include "../../../include/logic/factory/Bomber.h"
#include "../../../include/logic/factory/PowerUp.h"
#include "../../../include/utils/Stopwatch.h"

void Bomber::setPosition(const float x, const float y) {
    position.x = x;
    position.y = y;
}

Position Bomber::getPosition() const { return position; }

void Bomber::move(const float dx, const float dy) {
    const double deltaTime = utils::Stopwatch::getInstance().getDeltaTime();
    position.x += dx * speed * static_cast<float>(deltaTime);
    position.y += dy * speed * static_cast<float>(deltaTime);

    if (dx != 0 || dy != 0) {
        isMoving = true;
    }
}

void Bomber::moveDirectly(const float dx, const float dy) {
    position.x += dx;
    position.y += dy;

    if (dx != 0 || dy != 0) {
        isMoving = true;
    }
}

void Bomber::update(const float deltaTime) {
    if (!isMoving && wasMoving) {
        notify(*this, Event::BomberStopped);
    }
    wasMoving = isMoving;
    isMoving = false;

    if (bomb_cooldown_timer > 0.0f) {
        bomb_cooldown_timer -= deltaTime;
    }
}

Rect Bomber::getCollisionRect() const { return {position.x - 0.4f, position.y - 0.4f, 0.8f, 0.8f}; }

void Bomber::onNotify(const Entity& entity, const Event event) {
    if (event == Event::BombExploded) {
        number_of_bombs += 1;
    }
}

bool Bomber::canPlaceBomb() const {
    if (number_of_bombs > 0 && bomb_cooldown_timer <= 0.0f) {
        return true;
    }
    return false;
}

void Bomber::placeBomb() {
    number_of_bombs -= 1;
    bomb_cooldown_timer = BOMB_COOLDOWN;
}

int Bomber::getBlastRadius() const { return blast_radius; }

void Bomber::gainPowerUp(const PowerUpType type) {
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

void Bomber::triggerEvent(Event event) { notify(*this, event); }
