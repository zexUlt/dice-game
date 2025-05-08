#pragma once

#include "dices/dice.hpp"

#include <array>
#include <vector>

struct Player {
public:
    void RollDices();
    std::array<int, 6> GetDicesState() const;
    std::vector<int> SelectDices(std::vector<int> selection) const;

    int CurrentScore = 0;

private:
    std::array<Dice, 6> Dices_;
};
