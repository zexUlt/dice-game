#pragma once

#include "common/hash.hpp"
#include "dice.hpp"

#include <unordered_map>
#include <vector>

/**
    Dice scores
    1-6 == 1500 pts
    2-6 == 750 pts
    1-5 == 500 pts
    1 == 100 pts
    5 == 50 pts
    1x3 == 1000 pts
    2x3 == 200 pts
    3x3 == 300 pts
    4x3 == 400 pts
    5x3 == 500 pts
    6x3 == 600 pts

    Nx4 == Nx3 * 2 pts
    Nx5 == Nx4 * 2 pts
    Nx6 == Nx5 * 2 pts
*/

class ScoreCalculator {
public:
    ScoreCalculator();

    int GetScore(std::vector<int> selectedDices) const;

private:
    std::unordered_map<std::pair<int, int>, int> ScoreRules_;
};
