#ifndef BOMBERMAN_LOGIC_SCORE_H
#define BOMBERMAN_LOGIC_SCORE_H

#include <vector>
#include <string>
#include "Observer.h"

namespace logic {

/**
 * @brief Score entry for the scoreboard.
 */
struct ScoreEntry {
    std::string name;
    int score;
};

/**
 * @brief Manages scoring and persists the top 5 scores.
 * Acts as an observer to be notified of score-relevant events.
 */
class Score : public Observer {
public:
    Score();

    // Observer interface
    void update() override;

    void addPoints(int points);
    int getCurrentScore() const;

    void submitScore(const std::string& name);
    void saveScoreboard(const std::string& filename) const;
    void loadScoreboard(const std::string& filename);

    const std::vector<ScoreEntry>& getTopScores() const;

private:
    int currentScore;
    std::vector<ScoreEntry> topScores;
};

} // namespace logic

#endif // BOMBERMAN_LOGIC_SCORE_H
