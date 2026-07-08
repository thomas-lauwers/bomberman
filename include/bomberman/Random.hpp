#pragma once

#include <cstdint>
#include <random>

namespace bomberman {

class Random {
  public:
    static Random& instance();

    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    bool chance(double probability);
    int rangeInt(int minInclusive, int maxInclusive);
    double rangeReal(double minInclusive, double maxInclusive);
    void reseed(std::uint32_t seed);

  private:
    Random();

    std::mt19937 generator_;
};

} // namespace bomberman
