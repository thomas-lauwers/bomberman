#include "logic/Random.h"

namespace logic {

Random& Random::getInstance() {
    static Random instance;
    return instance;
}

Random::Random() {
    std::random_device rd;
    gen = std::mt19937(rd());
}

int Random::getRandomInt(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

float Random::getRandomFloat(float min, float max) {
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

} // namespace logic
