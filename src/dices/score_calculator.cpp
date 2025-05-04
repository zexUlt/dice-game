#include "dices/score_calculator.hpp"

#include <algorithm>

ScoreCalculator::ScoreCalculator() {
    // clang-format off
    ScoreRules_ = {
        {{1, 1}, 100},
        {{5, 1}, 50},
        {{21, 6}, 1500},
        {{20, 5}, 750},
        {{15, 5}, 500},
        {{3, 3}, 1000},
        {{6, 3}, 200},
        {{9, 3}, 300},
        {{12, 3}, 400},
        {{15, 3}, 500},
        {{18, 3}, 600}};
    // clang-format on
}

int ScoreCalculator::GetScore(const std::vector<int>& selectedDices) const {
    int totalScore = 0;

    return totalScore;
}
