#pragma once

#include "dices/score_calculator.hpp"
#include "player.hpp"

#include <array>

class GameState {
public:
    enum class ETurnResult {
        OK,
        NoMoves,
        BadSelection
    };

    GameState(int winningScore);

    bool IsGameOver(int& winner) const;

    int GetActivePlayer() const;
    int GetActivePlayerStashedScore() const;
    int GetActivePlayerUnstashedScore() const;
    std::pair<int, int> GetAllPlayersTotalScore() const;
    int GetWinningScore() const;
    std::vector<std::pair<int, int>> GetActivePlayerDices() const;

    void OnPlayerBeginPlay();
    ETurnResult ProcessTurn(const std::vector<int>& selectedDices);
    void OnPlayerStashScore();
    void OnPlayerFinishTurn();

    bool CheckMoves();

private:
    void PassTurn();

    int WinningScore_;
    int ActivePlayer_;
    ScoreCalculator ScoreCalculator_;
    std::array<Player, 2> Players_;
};
