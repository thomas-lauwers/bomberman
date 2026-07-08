#include "logic/Entity.h"
#include <algorithm>

namespace logic {

Entity::Entity(float x, float y) : x(x), y(y) {}

void Entity::getAABB(float& minX, float& minY, float& maxX, float& maxY) const {
    float hw = 0.06f;
    float hh = 0.06f;
    minX = x - hw;
    maxX = x + hw;
    minY = y - hh;
    maxY = y + hh;
}

void Entity::attach(Observer* observer) {
    observers.push_back(observer);
}

void Entity::detach(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Entity::notify() {
    for (auto observer : observers) {
        observer->update();
    }
}

} // namespace logic
