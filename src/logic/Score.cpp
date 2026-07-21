#include "../../include/logic/Score.h"

void Score::update(const float deltaTime) {
    timeAliveAccumulator += deltaTime;
    if (timeAliveAccumulator >= 1.0f) {
        const int seconds = static_cast<int>(timeAliveAccumulator);
        currentScore += seconds * POINTS_PER_SECOND;
        timeAliveAccumulator -= static_cast<float>(seconds);
    }
}

void Score::onNotify(const Entity& entity, const Event event) {
    switch (event) {
        case Event::PlayerBrokeBlock:
            addPoints(10);
            break;
        case Event::PlayerPickedUpPowerUp:
            addPoints(50);
            break;
        case Event::PlayerKilledEnemy:
            addPoints(500);
            break;
        case Event::GameWon:
            addPoints(1000);
            break;
        case Event::GameLost:
            addPoints(-500);
            break;
        default:
            break;
    }
}
