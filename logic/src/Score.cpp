#include "logic/Score.h"
#include <fstream>
#include <algorithm>

namespace logic {

Score::Score() : currentScore(0) {}

void Score::update() {
    // Logic to update score based on observed entity state changes
    // (e.g., entity death, block broken)
}

void Score::addPoints(int points) {
    currentScore += points;
}

int Score::getCurrentScore() const {
    return currentScore;
}

void Score::submitScore(const std::string& name) {
    topScores.push_back({name, currentScore});
    std::sort(topScores.begin(), topScores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
    });
    if (topScores.size() > 5) {
        topScores.resize(5);
    }
}

void Score::saveScoreboard(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : topScores) {
            file << entry.name << " " << entry.score << "\n";
        }
    }
}

void Score::loadScoreboard(const std::string& filename) {
    std::ifstream file(filename);
    topScores.clear();
    if (file.is_open()) {
        ScoreEntry entry;
        while (file >> entry.name >> entry.score) {
            topScores.push_back(entry);
        }
    }
}

const std::vector<ScoreEntry>& Score::getTopScores() const {
    return topScores;
}

} // namespace logic
