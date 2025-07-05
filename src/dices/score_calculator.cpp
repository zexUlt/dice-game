#include "dices/score_calculator.hpp"

#include <algorithm>
#include <utility>

ScoreCalculator::ScoreCalculator() {
    // clang-format off
    ScoreRules_ = {
        {{1, 1}, 100},
        {{1, 3}, 1000},
        {{5, 1}, 50},
        {{2, 3}, 200},
        {{3, 3}, 300},
        {{4, 3}, 400},
        {{5, 3}, 500},
        {{6, 3}, 600},
    };
    // clang-format on
}

bool ScoreCalculator::HasPossibleMoves(const std::vector<int>& selectedDices) const {
    std::array<int, 7> valuesCount = CountDiceValues(selectedDices);

    for (int i = 1; i < valuesCount.size(); ++i) {
        if ((i == 1 || i == 5) && valuesCount[i] > 0) {
            return true;
        }
        if (valuesCount[i] >= 3) {
            return true;
        }
    }

    return false;
}

int ScoreCalculator::GetScore(const std::vector<int>& selectedDices) const {
    int totalScore = 0;

    std::array<int, 7> valuesCount = CountDiceValues(selectedDices);

    // First pass to find longest contigious sequences
    // It's enough to look through 2 to 5
    bool sequenceFound = true;
    for (int i = 5; i > 1; --i) {
        if (valuesCount[i] == 0) {
            sequenceFound = false;
            break;
        }
    }

    if (sequenceFound) {
        if (valuesCount[1] != 0) {
            // There are two possible sequences 1-6 and 1-5
            if (valuesCount[6] != 0) {
                // Found 1-6, all dices used
                return 1500;
            } else {
                // 1-5 found
                totalScore = 500;
            }
        } else if (valuesCount[6] != 0) {
            // Sequence is from 2 to 6
            totalScore = 750;
        }

        int minIdx = 0;
        int maxIdx = 0;
        if (totalScore == 500) {
            minIdx = 1;
            maxIdx = 5;
        }
        if (totalScore == 750) {
            minIdx = 2;
            maxIdx = 6;
        }

        for (int i = minIdx; i <= maxIdx; ++i) {
            --valuesCount[i];
        }
    }

    // Second pass to find similar dices
    for (int i = 1; i <= 6; ++i) {
        if (valuesCount[i] == 0) {
            continue;
        }

        if (valuesCount[i] < 3) {
            if (!ScoreRules_.contains({i, 1})) {
                // Fast finish if it is less than 3 dices with values other than 1 or 5
                totalScore = 0;
                break;
            }
            totalScore += ScoreRules_.at(std::make_pair(i, 1)) * valuesCount[i];
            valuesCount[i] = 0;
        } else {
            totalScore += ScoreRules_.at(std::make_pair(i, 3)) << (valuesCount[i] - 3);
            valuesCount[i] = 0;
        }
    }

    if (std::ranges::any_of(valuesCount, [](int count) {
            return count > 0;
        })) {
        // Not all dices used, can't allow that
        totalScore = 0;
    }

    return totalScore;
}

std::array<int, 7> ScoreCalculator::CountDiceValues(const std::vector<int>& selectedDices) const {
    std::array<int, 7> valuesCount{};

    for (auto e : selectedDices) {
        ++valuesCount[e];
    }

    return valuesCount;
}
