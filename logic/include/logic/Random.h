#ifndef BOMBERMAN_LOGIC_RANDOM_H
#define BOMBERMAN_LOGIC_RANDOM_H

#include <random>

namespace logic {

/**
 * @brief Singleton class for random number generation using Mersenne Twister.
 */
class Random {
public:
    static Random& getInstance();

    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    int getRandomInt(int min, int max);
    float getRandomFloat(float min, float max);

private:
    Random();
    std::mt19937 gen;
};

} // namespace logic

#endif // BOMBERMAN_LOGIC_RANDOM_H
