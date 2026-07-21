#ifndef BOMBERMAN_SCORE_H
#define BOMBERMAN_SCORE_H

class Score {
public:
    Score() : currentScore(0), timeAliveAccumulator(0.0f) {}
    
    void update(float deltaTime);
    [[nodiscard]] int getCurrentScore() const { return currentScore; }

private:
    int currentScore;
    float timeAliveAccumulator;
    const int POINTS_PER_SECOND = 1;
};

#endif
