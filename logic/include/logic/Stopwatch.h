#ifndef BOMBERMAN_LOGIC_STOPWATCH_H
#define BOMBERMAN_LOGIC_STOPWATCH_H

#include <chrono>

namespace logic {

/**
 * @brief Singleton class for time management using std::chrono.
 */
class Stopwatch {
public:
    static Stopwatch& getInstance();

    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    /**
     * @brief Get elapsed time since last tick in seconds.
     */
    float getDeltaTime() const;
    
    void tick();
    void reset();

private:
    Stopwatch();
    std::chrono::steady_clock::time_point lastTime;
    float deltaTime;
};

} // namespace logic

#endif // BOMBERMAN_LOGIC_STOPWATCH_H
