#pragma once

#include <optional>
#include <string>
#include <vector>

class UserInputComponent {
public:
    enum class EParseResult {
        OK,
        NonDigitInput,
        TooMuchInput
    };

    std::pair<bool, std::optional<std::string_view>> AskForDiceSelection(std::vector<int>& outSelection) const;
    EParseResult ParseUserSelectedDices(const std::string& userInput, std::vector<int>& outSelectedDices) const;
    bool ValidateSelectedDices(const std::vector<int>& selectedDices) const;
    void NormalizeSelectedDices(std::vector<int>& selectedDices) const;
};
