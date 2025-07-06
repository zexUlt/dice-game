#include "app/user_input_component.hpp"

#include "common/exceptions.hpp"

#include <algorithm>
#include <cctype>
#include <exception>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>

std::pair<UserInputComponent::InputResult, std::optional<std::string_view>>
UserInputComponent::AskForInput(std::vector<int>& outSelection) const {
    std::string buf;
    if (!std::getline(std::cin, buf)) {
        throw UserInputException("Can't read stdin");
    }

    if (!std::isdigit(buf[0])) {
        if (buf.size() > 1) {
            return {InputResult::Error, "Unknown command. Try again"};
        }

        if (std::tolower(buf[0]) == STASH_COMMAND) {
            return {InputResult::Stash, std::nullopt};
        }

        if (std::tolower(buf[0]) == FINISH_COMMAND) {
            return {InputResult::Finish, std::nullopt};
        }
    }

    switch (ParseUserSelectedDices(buf, outSelection)) {
        case EParseResult::NonDigitInput: {
            return {InputResult::Error, "Please, enter digits from 1 to 6 only\n"};
        }
        case EParseResult::TooMuchInput: {
            return {InputResult::Error, "No more than 6 digits expected\n"};
        }
        case EParseResult::OK: {
            if (!ValidateSelectedDices(outSelection)) {
                outSelection.clear();
                return {InputResult::Error, "Digits from [1, 6] range are expected\n"};
            }
            break;
        }
    }

    return {InputResult::DiceSelect, std::nullopt};
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
