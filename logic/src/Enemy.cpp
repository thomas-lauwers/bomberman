#include "logic/Enemy.h"
#include "logic/World.h"
#include "logic/Random.h"

namespace logic {

Enemy::Enemy(float x, float y, int behaviorType)
    : Entity(x, y), behaviorType(behaviorType), dead(false), moveCounter(0), curDx(0), curDy(0) {}

void Enemy::update() {
    // Entities can have their own update logic here
}

bool Enemy::isAlive() const { return !dead; }

void Enemy::kill() {
    dead = true;
    notify();
}

void Enemy::performAI(World& world) {
    if (dead) return;
    
    // Simple AI: Move randomly, but could be expanded to flee bombs, etc.
    // For a battle mode, even basic random movement makes it playable.
    
    if (moveCounter <= 0) {
        int dir = Random::getInstance().getRandomInt(0, 4);
        curDx = 0; curDy = 0;
        if (dir == 0) curDx = 1;
        else if (dir == 1) curDx = -1;
        else if (dir == 2) curDy = 1;
        else if (dir == 3) curDy = -1;
        
        // Vary behavior slightly based on type
        moveCounter = 15 + behaviorType * 5;
    }
    
    moveCounter--;
    world.moveEnemy(*this, curDx, curDy);
}

} // namespace logic
