#include "game/game_state.hpp"
#include "game/player.hpp"

GameState::GameState(int winningScore)
    : WinningScore_(winningScore)
    , ActivePlayer_(0) {
}

bool GameState::IsGameOver(int& winner) const {
    for (int i = 0; i < Players_.size(); ++i) {
        if (Players_[i].TotalScore > WinningScore_) {
            winner = i + 1;
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
    activePlayer.FinishRound();
    activePlayer.RollDices();
}

void GameState::OnPlayerFinishTurn() {
    auto& activePlayer = Players_[ActivePlayer_];

    activePlayer.FinishRound();
    activePlayer.FinishTurn();

    PassTurn();
}

void GameState::OnPlayerBeginPlay() {
    auto& activePlayer = Players_[ActivePlayer_];

    activePlayer.RollDices();
}

GameState::ETurnResult GameState::ProcessTurn(const std::vector<int>& selectedDices) {
    if (!CheckMoves()) {
        return ETurnResult::NoMoves;
    }

    auto& activePlayer       = Players_[ActivePlayer_];
    auto selectedDicesValues = activePlayer.SelectDices(selectedDices);

    auto playerScore = ScoreCalculator_.GetScore(selectedDicesValues);

    if (playerScore == 0) {
        return ETurnResult::BadSelection;
    }

    activePlayer.SaveLastSelectedDices(selectedDices);
    activePlayer.UnstashedScore += playerScore;

    return ETurnResult::OK;
}

bool GameState::CheckMoves() {
    const auto& activeDicesWithIndicies = GetActivePlayerDices();
    std::vector<int> activeDices;
    activeDices.reserve(activeDicesWithIndicies.size());
    for (const auto [_, value] : activeDicesWithIndicies) {
        activeDices.push_back(value);
    }

    return ScoreCalculator_.HasPossibleMoves(activeDices);
}