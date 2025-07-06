#pragma once

#include "app/user_input_component.hpp"
#include "game/game_state.hpp"

#include <iostream>

class App {
public:
    App(int argc, char** argv);

    void Run();

private:
    template <typename... Args>
    void WriteDebugMessage(Args... args) const {
        ((std::cout << "Debug") << ... << args);
    }

    void WriteMessage(std::string_view message) const;
    void DisplayGameStatus() const;

    void DisplayDices() const;

    UserInputComponent UserInputHandler_;
    GameState GameState_;

    static constexpr std::string_view USER_MESSAGE_WRAPS = "#====================#";
    static constexpr std::string_view CONTROLS_HINT =
        R"(Select dices by entering their indexes delimetered with spaces or choose action
 [S/s] to stash current score and continue
 [E/e] to save score and pass turn
)";
    static constexpr std::string_view SCORE_TABLE =
        R"(
#==P1====Goal====P2==#
# {:4} | {:4} | {:4} #
# {:4} |      | {:4} #
# {:4} |      | {:4} #
#====================#
)";
};
