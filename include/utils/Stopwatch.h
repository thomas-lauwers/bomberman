#ifndef BOMBERMAN_STOPWATCH_H
#define BOMBERMAN_STOPWATCH_H

#include <chrono>

namespace utils {
class Stopwatch {
public:
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    static Stopwatch& getInstance() {
        static Stopwatch instance;
        return instance;
    }

    void update();
    [[nodiscard]] double getDeltaTime() const;

private:
    Stopwatch();

    std::chrono::steady_clock::time_point lastTick;
    double deltaTime;
};
} // namespace utils

#endif // BOMBERMAN_STOPWATCH_H
