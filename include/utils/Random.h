#ifndef BOMBERMAN_RANDOM_H
#define BOMBERMAN_RANDOM_H

#include <random>

namespace utils {
class Random {
public:
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    static Random& getInstance() {
        static Random instance;
        return instance;
    }

    bool roll(float chance);
    int getInt();

private:
    Random() = default;

    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<> dist{0, 1};
    std::uniform_int_distribution<> distInt{0, 2};
};
} // namespace utils

#endif // BOMBERMAN_RANDOM_H
