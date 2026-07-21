#include "../../include/logic/Score.h"
#include <fstream>
#include <algorithm>
#include <iostream>

Score::Score() : currentScore{0}, timeAliveAccumulator{0.0f} {
    loadHighScores();
}

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

void Score::loadHighScores() {
    highScores.clear();
    std::ifstream file("./data/highscores.txt");
    int score;
    while (file >> score) {
        highScores.push_back(score);
    }
    std::sort(highScores.rbegin(), highScores.rend());
    if (highScores.size() > 5) {
        highScores.resize(5);
    }
}

void Score::saveFinalScore() {
    highScores.push_back(currentScore);
    std::sort(highScores.rbegin(), highScores.rend());
    if (highScores.size() > 5) {
        highScores.resize(5);
    }

    std::ofstream file("./data/highscores.txt");
    for (const int score : highScores) {
        file << score << "\n";
    }
}
