#include "app/app.hpp"

#include "common/exceptions.hpp"
#include "enums/game_state.hpp"

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

void App::Run() {
    while (!GameState_.IsGameOver()) {
        ETurnState currentTurnState = ETurnState::TurnStart;
        switch (currentTurnState) {
            case ETurnState::TurnStart: {
                GameState_.ProcessTurnStart();
                currentTurnState = ETurnState::DiceSelect;
            }
            case ETurnState::DiceSelect: {
                // if (GameState_.ProcessTurnMid(const std::vector<int>& selectedDices))
            }
            case ETurnState::TurnContinue: {
            }
            case ETurnState::TurnEnd: {
            }
            default:
                break;
        }
    }
}

std::vector<int> App::AskForDiceSelection() const {
    std::cout << "Select dices by entering their indexes delimetered with spaces:\n";

    std::string buf;
    if (!std::getline(std::cin, buf)) {
        throw UserInputException();
    }

    std::vector<int> selection;
    selection.reserve(6);
}

bool ParseUserSelectedDices(const std::string& userInput, std::vector<int>& outSelectedDices) {
    std::istringstream iss(userInput);

    std::string token;
    while (std::getline(iss, token, ' ')) {
        try {
            outSelectedDices.push_back(std::stoi(token));
        } catch (std::exception&) {
            return false;
        }
    }

    if (outSelectedDices.size() > 6) {
        return false;
    }

    return true;
}
