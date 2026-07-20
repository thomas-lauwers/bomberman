#include "../../include/utils/Random.h"

namespace utils {
bool Random::roll(const float chance) {
    if (dist(gen) <= chance) {
        return true;
    }

    return false;
}

int Random::getInt() {
    return distInt(gen);
}
}