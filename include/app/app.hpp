#pragma once

#include "game/game_state.hpp"

#include <string_view>

class App {
public:
    void Run();

    std::vector<int> AskForDiceSelection() const;

private:
    bool ParseUserSelectedDices(const std::string& userInput, std::vector<int>& outSelectedDices);

    GameState GameState_;
};
