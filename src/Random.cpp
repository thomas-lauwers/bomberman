#include "bomberman/Random.hpp"

#include <algorithm>

namespace bomberman {

Random::Random() : generator_(std::random_device{}()) {}

Random& Random::instance() {
    static Random random;
    return random;
}

bool Random::chance(const double probability) {
    return rangeReal(0.0, 1.0) <= std::clamp(probability, 0.0, 1.0);
}

int Random::rangeInt(const int minInclusive, const int maxInclusive) {
    std::uniform_int_distribution<int> distribution(minInclusive, maxInclusive);
    return distribution(generator_);
}

double Random::rangeReal(const double minInclusive, const double maxInclusive) {
    std::uniform_real_distribution<double> distribution(minInclusive, maxInclusive);
    return distribution(generator_);
}

void Random::reseed(const std::uint32_t seed) { generator_.seed(seed); }

} // namespace bomberman
