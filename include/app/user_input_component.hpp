#pragma once

#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

class UserInputComponent {
public:
    enum class EParseResult {
        OK,
        NonDigitInput,
        TooMuchInput
    };

    enum class InputResult {
        Error,
        Stash,
        Finish,
        DiceSelect
    };

    std::pair<InputResult, std::optional<std::string_view>> AskForInput(std::vector<int>& outSelection) const;
    EParseResult ParseUserSelectedDices(const std::string& userInput, std::vector<int>& outSelectedDices) const;
    bool ValidateSelectedDices(const std::vector<int>& selectedDices) const;
    void NormalizeSelectedDices(std::vector<int>& selectedDices) const;

private:
    static constexpr char STASH_COMMAND = 's';
    static constexpr char FINISH_COMMAND = 'e';
};
