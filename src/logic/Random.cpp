#include "../../include/logic/Random.h"

bool Random::roll(const float chance) {
    if (dist(gen) <= chance) {
        return true;
    }

    return false;
}
