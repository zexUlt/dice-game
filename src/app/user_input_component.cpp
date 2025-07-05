#include "app/user_input_component.hpp"

#include "common/exceptions.hpp"

#include <algorithm>
#include <exception>
#include <iostream>
#include <optional>
#include <vector>
#include <sstream>

std::pair<bool, std::optional<std::string_view>> UserInputComponent::AskForDiceSelection(std::vector<int>& outSelection) const {
    std::string buf;
    if (!std::getline(std::cin, buf)) {
        throw UserInputException("Can't read stdin");
    }

    switch (ParseUserSelectedDices(buf, outSelection)) {
        case EParseResult::NonDigitInput: {
            return {false, "Please, enter digits from 1 to 6 only\n"};
        }
        case EParseResult::TooMuchInput: {
            return {false, "No more than 6 digits expected\n"};
        }
        case EParseResult::OK: {
            if (!ValidateSelectedDices(outSelection)) {
                outSelection.clear();
                return {false, "Digits from [1, 6] range are expected\n"};
            }
            break;
        }
    }

    return {true, std::nullopt};
}

UserInputComponent::EParseResult UserInputComponent::ParseUserSelectedDices(const std::string& userInput,
                                                                            std::vector<int>& outSelectedDices) const {
    std::istringstream iss(userInput);

    std::string token;
    while (std::getline(iss, token, ' ')) {
        try {
            outSelectedDices.push_back(std::stoi(token));
        } catch (std::exception&) {
            outSelectedDices.clear();
            return EParseResult::NonDigitInput;
        }
    }

    if (outSelectedDices.size() > 6) {
        outSelectedDices.clear();
        return EParseResult::TooMuchInput;
    }

    return EParseResult::OK;
}

bool UserInputComponent::ValidateSelectedDices(const std::vector<int>& selectedDices) const {
    return std::all_of(selectedDices.begin(), selectedDices.end(), [](int el) {
        return el >= 1 and el <= 6;
    });
}
