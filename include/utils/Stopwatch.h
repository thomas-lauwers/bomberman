/**
 * @file Stopwatch.h
 * @brief Defines the Stopwatch utility class for time tracking.
 */

#ifndef BOMBERMAN_STOPWATCH_H
#define BOMBERMAN_STOPWATCH_H

#include <chrono>

namespace utils {

/**
 * @class Stopwatch
 * @brief Singleton class for tracking time and delta time between updates.
 */
class Stopwatch {
public:
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    /**
     * @brief Gets the singleton instance of the Stopwatch class.
     * @return Reference to the Stopwatch instance.
     */
    static Stopwatch& getInstance() {
        static Stopwatch instance;
        return instance;
    }

    /**
     * @brief Updates the internal clock and calculates delta time.
     */
    void update();

    /**
     * @brief Gets the elapsed time since the last update in seconds.
     * @return Delta time in seconds.
     */
    [[nodiscard]] double getDeltaTime() const;

private:
    /**
     * @brief Private constructor for singleton.
     */
    Stopwatch();

    std::chrono::steady_clock::time_point lastTick; ///< Time point of the last update
    double deltaTime;                               ///< Time elapsed since last update
};
} // namespace utils

#endif // BOMBERMAN_STOPWATCH_H
