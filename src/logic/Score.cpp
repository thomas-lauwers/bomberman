#include "../../include/logic/Score.h"

void Score::update(const float deltaTime) {
    timeAliveAccumulator += deltaTime;
    if (timeAliveAccumulator >= 1.0f) {
        const int seconds = static_cast<int>(timeAliveAccumulator);
        currentScore += seconds * POINTS_PER_SECOND;
        timeAliveAccumulator -= static_cast<float>(seconds);
    }
}
