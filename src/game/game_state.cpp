#include "game/game_state.hpp"

#include "debug/debug.hpp"
#include "game/player.hpp"

GameState::GameState(int winningScore)
    : WinningScore_(winningScore)
    , ActivePlayer_(0) {
}

bool GameState::IsGameOver() const {
    for (const auto& player : Players_) {
        if (player.TotalScore > WinningScore_) {
            return true;
        }
    }

    return false;
}

int GameState::GetActivePlayer() const {
    return ActivePlayer_;
}

int GameState::GetActivePlayerStashedScore() const {
    return Players_[ActivePlayer_].StashedScore;
}

int GameState::GetActivePlayerUnstashedScore() const {
    return Players_[ActivePlayer_].UnstashedScore;
}

int GameState::GetWinningScore() const {
    return WinningScore_;
}

std::pair<int, int> GameState::GetAllPlayersTotalScore() const {
    return {Players_[0].TotalScore, Players_[1].TotalScore};
}

std::vector<std::pair<int, int>> GameState::GetActivePlayerDices() const {
    return Players_.at(ActivePlayer_).GetDicesState();
}

void GameState::PassTurn() {
    ActivePlayer_ = 1 - ActivePlayer_;
}

void GameState::OnPlayerStashScore() {
    auto& activePlayer = Players_[ActivePlayer_];

    activePlayer.RollDices();
}

void GameState::OnPlayerEndTurn() {
    auto& activePlayer = Players_[ActivePlayer_];

    activePlayer.TotalScore += activePlayer.StashedScore;
    activePlayer.StashedScore = 0;

    PassTurn();
}

void GameState::OnPlayerBeginPlay() {
    auto& activePlayer = Players_[ActivePlayer_];

    activePlayer.RollDices();
}

GameState::ETurnResult GameState::ProcessTurn(const std::vector<int>& selectedDices) {
    const auto& activeDicesWithIndicies = GetActivePlayerDices();
    std::vector<int> activeDices;
    activeDices.reserve(activeDicesWithIndicies.size());
    for (const auto [_, value] : activeDicesWithIndicies) {
        activeDices.push_back(value);
    }

    if (!ScoreCalculator_.HasPossibleMoves(activeDices)) {
        return ETurnResult::NoMoves;
    }

    auto& activePlayer       = Players_[ActivePlayer_];
    auto selectedDicesValues = activePlayer.SelectDices(selectedDices);
    LOG_DEBUG_ARRAY(selectedDices);
    LOG_DEBUG_ARRAY(selectedDicesValues);
    auto playerScore = ScoreCalculator_.GetScore(selectedDicesValues);
    LOG_DEBUG(playerScore)
    if (playerScore == 0) {
        return ETurnResult::BadSelection;
    }

    activePlayer.StashedScore += playerScore;

    return ETurnResult::OK;
}
