#pragma once

#include "dices/dice.hpp"

#include <array>
#include <unordered_set>
#include <vector>

struct Player {
public:
    Player();
    
    void RollDices();
    void UpdateStashedDices(const std::vector<int>& stashedIndices);

    std::vector<std::pair<int, int>> GetDicesState() const;
    std::vector<int> SelectDices(std::vector<int> selection) const;

    int TotalScore     = 0;
    int StashedScore   = 0;
    int UnstashedScore = 0;

private:
    std::unordered_set<int> StashedDices_;
    std::array<Dice, 6> Dices_;
};
