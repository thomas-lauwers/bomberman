#ifndef BOMBERMAN_SCORE_H
#define BOMBERMAN_SCORE_H

#include <vector>
#include "Observer.h"

class Score : public Observer {
public:
    Score();
    
    void update(float deltaTime);
    void addPoints(const int points) { currentScore += points; }
    [[nodiscard]] int getCurrentScore() const { return currentScore; }
    [[nodiscard]] const std::vector<int>& getHighScores() const { return highScores; }

    void onNotify(const Entity& entity, Event event) override;
    void saveFinalScore();

private:
    void loadHighScores();

    int currentScore;
    float timeAliveAccumulator;
    std::vector<int> highScores;
    const int POINTS_PER_SECOND = 1;
};

#endif
