/**
 * @file Random.h
 * @brief Defines the Random utility class for generating random numbers.
 */

#ifndef BOMBERMAN_RANDOM_H
#define BOMBERMAN_RANDOM_H

#include <random>

namespace utils {

/**
 * @class Random
 * @brief Singleton class for generating random numbers.
 */
class Random {
public:
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    /**
     * @brief Gets the singleton instance of the Random class.
     * @return Reference to the Random instance.
     */
    static Random& getInstance() {
        static Random instance;
        return instance;
    }

    /**
     * @brief Performs a random roll based on a given chance.
     * @param chance Probability of the roll returning true (0.0 to 1.0).
     * @return True if the roll succeeds, false otherwise.
     */
    bool roll(float chance);

    /**
     * @brief Gets a random integer between 0 and 2.
     * @return A random integer.
     */
    int getInt();

private:
    /**
     * @brief Private constructor for singleton.
     */
    Random() = default;

    std::mt19937 gen{std::random_device{}()};      ///< Random number generator
    std::uniform_real_distribution<> dist{0, 1};   ///< Real number distribution
    std::uniform_int_distribution<> distInt{0, 2}; ///< Integer distribution
};
} // namespace utils

#endif // BOMBERMAN_RANDOM_H
