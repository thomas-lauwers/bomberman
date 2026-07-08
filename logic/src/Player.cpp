#include "logic/Player.h"

namespace logic {

Player::Player(float x, float y)
    : Entity(x, y), speed(0.05f), bombRange(1), bombCapacity(1), activeBombs(0), dead(false) {}

void Player::update() {
    // Basic player logic (moving is handled by move() called by Game)
}

bool Player::isAlive() const { return !dead; }

void Player::move(float dx, float dy) {
    x += dx * speed;
    y += dy * speed;
    notify();
}

bool Player::canPlaceBomb() const {
    return activeBombs < bombCapacity;
}

void Player::placeBomb() {
    if (canPlaceBomb()) {
        activeBombs++;
        // Notify or return something to World to create a bomb
    }
}

void Player::onBombExploded() {
    if (activeBombs > 0) activeBombs--;
}

void Player::increaseRange() { bombRange++; }
void Player::increaseBombCapacity() { bombCapacity++; }
void Player::increaseSpeed() { speed += 0.01f; }

void Player::kill() {
    dead = true;
    notify();
}

} // namespace logic
