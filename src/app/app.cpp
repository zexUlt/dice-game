#include "app/app.hpp"

#include "app/user_input_component.hpp"
#include "enums/game_state.hpp"
#include "game/game_state.hpp"

#include <format>
#include <iostream>
#include <vector>

App::App([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
    : GameState_(1500) {
}

void App::Run() {
    ETurnState currentTurnState = ETurnState::TurnStart;
    int winner;
    while (!GameState_.IsGameOver(winner)) {
        switch (currentTurnState) {
            case ETurnState::TurnStart: {
                WriteMessage(std::format("Player{}'s turn", GameState_.GetActivePlayer() + 1));
                GameState_.OnPlayerBeginPlay();
                currentTurnState = ETurnState::DiceSelect;
                break;
            }
            case ETurnState::DiceSelect: {
                if (!GameState_.CheckMoves()) {
                    WriteMessage("Bad luck! No possible selection");
                    currentTurnState = ETurnState::TurnEnd;
                    break;
                }

                std::vector<int> selection;
                WriteMessage(CONTROLS_HINT);
                DisplayDices();
                const auto [result, message] = UserInputHandler_.AskForInput(selection);
                bool resume                  = false;
                switch (result) {
                    case UserInputComponent::InputResult::Error: {
                        WriteMessage(*message);
                        break;
                    }
                    case UserInputComponent::InputResult::Stash: {
                        GameState_.OnPlayerStashScore();
                        DisplayGameStatus();
                        break;
                    }
                    case UserInputComponent::InputResult::Finish: {
                        GameState_.OnPlayerFinishTurn();
                        currentTurnState = ETurnState::TurnEnd;
                        break;
                    }
                    case UserInputComponent::InputResult::DiceSelect: {
                        resume = true;
                        break;
                    }
                }

                if (!resume) {
                    break;
                }

                switch (GameState_.ProcessTurn(selection)) {
                    case GameState::ETurnResult::NoMoves: {
                        // No possible moves for the player
                        // End turn
                        WriteMessage("Bad luck! No possible selection");
                        currentTurnState = ETurnState::TurnEnd;
                        break;
                    }
                    case GameState::ETurnResult::BadSelection: {
                        WriteMessage("Selection's score: 0");
                        break;
                    }
                    case GameState::ETurnResult::OK: {
                        DisplayGameStatus();
                    }
                }
                break;
            }
            case ETurnState::TurnEnd: {
                currentTurnState = ETurnState::TurnStart;
                DisplayGameStatus();
                break;
            }
            default:
                break;
        }
    }

    WriteMessage(std::format("Player {} is a winner!!!", winner));
}

void App::WriteMessage(std::string_view message) const {
    std::cout << std::format("> {}\n", message);
}

void App::DisplayGameStatus() const {
    const auto& [p1TotalScore, p2TotalScore] = GameState_.GetAllPlayersTotalScore();

    int p1StashedScore = 0;
    int p2StashedScore = 0;

    (GameState_.GetActivePlayer() == 0 ? p1StashedScore : p2StashedScore) = GameState_.GetActivePlayerStashedScore();

    int p1UnstashedScore = 0;
    int p2UnstashedScore = 0;

    (GameState_.GetActivePlayer() == 0 ? p1UnstashedScore : p2UnstashedScore) =
        GameState_.GetActivePlayerUnstashedScore();

    std::cout << std::format(SCORE_TABLE, p1TotalScore, GameState_.GetWinningScore(), p2TotalScore, p1StashedScore,
                             p2StashedScore, p1UnstashedScore, p2UnstashedScore)
              << std::endl;
}

void App::DisplayDices() const {
    const auto& dices = GameState_.GetActivePlayerDices();
    std::string displayStringIndicies;
    std::string displayStringValues;
    for (const auto [idx, value] : dices) {
        displayStringIndicies += std::format("[{}] ", idx);
        displayStringValues += std::format(" {}  ", value);
    }
    displayStringIndicies.pop_back();
    displayStringValues.pop_back();
    std::cout << std::format("> {}\n> {}\n", displayStringIndicies, displayStringValues);
}