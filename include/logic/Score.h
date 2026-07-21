#ifndef BOMBERMAN_SCORE_H
#define BOMBERMAN_SCORE_H

#include "Observer.h"

class Score : public Observer {
public:
    Score() : currentScore(0), timeAliveAccumulator(0.0f) {}
    
    void update(float deltaTime);
    void addPoints(const int points) { currentScore += points; }
    [[nodiscard]] int getCurrentScore() const { return currentScore; }

    void onNotify(const Entity& entity, Event event) override;

private:
    int currentScore;
    float timeAliveAccumulator;
    const int POINTS_PER_SECOND = 1;
};

#endif
