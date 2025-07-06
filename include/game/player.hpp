#pragma once

#include "dices/dice.hpp"

#include <array>
#include <unordered_set>
#include <vector>

struct Player {
public:
    Player();
    
    void RollDices();
    void FinishRound();
    void FinishTurn();
    void SaveLastSelectedDices(const std::vector<int>& selectedDices);

    std::vector<std::pair<int, int>> GetDicesState() const;
    std::vector<int> SelectDices(const std::vector<int>& selection) const;

    int TotalScore     = 0;
    int StashedScore   = 0;
    int UnstashedScore = 0;

private:
    std::vector<int> LastSelectedDices_;
    std::unordered_set<int> StashedDices_;
    std::array<Dice, 6> Dices_;
};
