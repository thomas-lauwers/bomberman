/**
 * @file Score.h
 * @brief Defines the Score class, responsible for tracking game points and high scores.
 */

#ifndef BOMBERMAN_SCORE_H
#define BOMBERMAN_SCORE_H

#include <vector>
#include "Observer.h"

/**
 * @class Score
 * @brief Manages the game score, tracking player performance and persisting high scores.
 *
 * The Score class tracks points earned through gameplay (time alive, blocks broken, etc.)
 * and maintains a list of top 5 high scores. It implements the Observer pattern to receive
 * scoring-related events.
 */
class Score : public Observer {
public:
    /**
     * @brief Constructs a new Score instance.
     */
    Score();
    
    /**
     * @brief Updates the score based on time elapsed.
     * @param deltaTime The time elapsed since the last update.
     */
    void update(float deltaTime);
    
    /**
     * @brief Adds points to the current score.
     * @param points The number of points to add.
     */
    void addPoints(const int points) { currentScore += points; }
    
    /**
     * @brief Gets the current score.
     * @return The current score.
     */
    [[nodiscard]] int getCurrentScore() const { return currentScore; }
    
    /**
     * @brief Gets the list of top 5 high scores.
     * @return A vector containing the high scores.
     */
    [[nodiscard]] const std::vector<int>& getHighScores() const { return highScores; }

    /**
     * @brief Handles scoring events received through the Observer pattern.
     * @param entity The entity that triggered the event.
     * @param event The event type.
     */
    void onNotify(const Entity& entity, Event event) override;
    
    /**
     * @brief Saves the final score to the high scores list and persists it to a file.
     */
    void saveFinalScore();

private:
    /**
     * @brief Loads the high scores from a file.
     */
    void loadHighScores();

    int currentScore;
    float timeAliveAccumulator;
    std::vector<int> highScores;
    const int POINTS_PER_SECOND = 1;
};

#endif
