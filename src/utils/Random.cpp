#include "../../include/utils/Random.h"

bool Random::roll(const float chance) {
    if (dist(gen) <= chance) {
        return true;
    }

    return false;
}

int Random::getInt(const int min, const int max) {
    return std::uniform_int_distribution(min, max)(gen);
}