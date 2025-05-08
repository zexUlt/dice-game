#include "game/game_state.hpp"

#include "game/player.hpp"

GameState::GameState(int winningScore)
    : WinningScore_(winningScore)
    , ActivePlayer_(0) {
}

bool GameState::IsGameOver() const {
    for (const auto& player : Players_) {
        if (player.CurrentScore > WinningScore_) {
            return true;
        }
    }

    return false;
}

int GameState::GetActivePlayer() const {
    return ActivePlayer_;
}

std::array<int, 6> GameState::GetActivePlayerDices() const {
    return Players_.at(ActivePlayer_).GetDicesState();
}

void GameState::PassTurn() {
    ActivePlayer_ = 1 - ActivePlayer_;
}

void GameState::ProcessTurnEnd() {
}

void GameState::ProcessTurnStart() {
    auto& activePlayer = Players_[ActivePlayer_];

    activePlayer.RollDices();
}

bool GameState::ProcessTurnMid(const std::vector<int>& selectedDices) {
    if (!ScoreCalculator_.HasPossibleMoves(selectedDices)) {
        return false;
    }

    return true;
}
