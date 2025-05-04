#include "dices/dice.hpp"
#include "dices/score_calculator.hpp"

#include <gtest/gtest.h>
#include <vector>

TEST(TestScoreCalculator, RepeatSameDice) {
    using Parametrize = std::pair<std::vector<int>, int>;
    // clang-format off
    std::vector<Parametrize> parametrize{
        {{1}, 100},
        {{1, 1}, 200},
        {{1, 1, 1}, 1000},
        {{1, 1, 1, 1}, 2000},
        {{1, 1, 1, 1, 1}, 4000},
    };
    // clang-format on

    ScoreCalculator scoreCalc;
    for(const auto& [param, assertion] : parametrize) {
        EXPECT_EQ(scoreCalc.GetScore(param), assertion);
    }
}
