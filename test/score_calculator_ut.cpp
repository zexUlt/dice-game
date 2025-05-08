#include "dices/dice.hpp"
#include "dices/score_calculator.hpp"

#include <gtest/gtest.h>
#include <numeric>
#include <vector>

namespace {

    std::vector<int> MakeVector(int diceCount, int diceValue = -1) {
        if (diceValue == -1) {
            return std::vector<int>(diceCount);
        }

        return std::vector<int>(diceCount, diceValue);
    }

} // namespace

TEST(TestScoreCalculator, RepeatOnes) {
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
    for (const auto& [param, assertion] : parametrize) {
        EXPECT_EQ(scoreCalc.GetScore(param), assertion);
    }
}

TEST(TestScoreCalculator, Triplets) {
    ScoreCalculator scoreCalc;
    for (int diceValue : {2, 3, 4, 6}) {
        for (int diceCount = 1; diceCount < 5; ++diceCount) {
            auto score = scoreCalc.GetScore(MakeVector(diceCount, diceValue));
            if (diceCount < 3) {
                EXPECT_EQ(score, 0) << "Dices other than 1 or 5 cannot combine in less than 3. Given value="
                                    << diceValue << " count=" << diceCount;
            } else {
                EXPECT_EQ(score, (diceValue * 100) << (diceCount - 3))
                    << "Wrong total score for dice with value " << diceValue << " and count " << diceCount;
            }
        }
    }
}

TEST(TestScoreCalculator, LongCombos) {
    ScoreCalculator scoreCalc;
    {
        // Test 1-6 combo
        auto selectedDices = MakeVector(6);
        std::iota(selectedDices.begin(), selectedDices.end(), 1);
        EXPECT_EQ(scoreCalc.GetScore(selectedDices), 1500) << "Wrong score for 1-6 sequence";
    }
    {
        // Test 1-5 combo
        auto selectedDices = MakeVector(5);
        std::iota(selectedDices.begin(), selectedDices.end(), 1);
        EXPECT_EQ(scoreCalc.GetScore(selectedDices), 500) << "Wrong score for 1-5 sequence";
    }
    {
        // Test 2-6 combo
        auto selectedDices = MakeVector(5);
        std::iota(selectedDices.begin(), selectedDices.end(), 2);
        EXPECT_EQ(scoreCalc.GetScore(selectedDices), 750) << "Wrong score for 2-6 sequence";
    }
}

TEST(TestScoreCalculator, NonExhaustiveSelection) {
    ScoreCalculator scoreCalc;

    std::vector<int> selectedDices{1, 1, 2, 5, 5};

    EXPECT_EQ(scoreCalc.GetScore(selectedDices), 0);
}
