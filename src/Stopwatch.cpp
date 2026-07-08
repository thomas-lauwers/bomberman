#include "bomberman/Stopwatch.hpp"

namespace bomberman {

Stopwatch::Stopwatch() : previous_(std::chrono::steady_clock::now()) {}

Stopwatch& Stopwatch::instance() {
    static Stopwatch stopwatch;
    return stopwatch;
}

double Stopwatch::tick() {
    const auto now = std::chrono::steady_clock::now();
    deltaTimeSeconds_ = std::chrono::duration<double>(now - previous_).count();
    previous_ = now;
    return deltaTimeSeconds_;
}

void Stopwatch::reset() {
    previous_ = std::chrono::steady_clock::now();
    deltaTimeSeconds_ = 0.0;
}

} // namespace bomberman
