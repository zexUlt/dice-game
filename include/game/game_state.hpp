#pragma once

#include "dices/score_calculator.hpp"
#include "player.hpp"

#include <array>

class GameState {
public:
    GameState(int winningScore);

    bool IsGameOver() const;
    int GetActivePlayer() const;
    std::array<int, 6> GetActivePlayerDices() const;
    void PassTurn();
    void ProcessTurnStart();
    bool ProcessTurnMid(const std::vector<int>& selectedDices);
    void ProcessTurnEnd();

private:
    int WinningScore_;
    int ActivePlayer_;
    ScoreCalculator ScoreCalculator_;
    std::array<Player, 2> Players_;
};
