#include "app/user_input_component.hpp"

#include <gtest/gtest.h>
#include <vector>

TEST(TestUserInput, OkDiceSelection) {
    UserInputComponent userInputComponent;
    const std::string userInput{"1 2 3"};
    std::vector<int> selectedDices;

    UserInputComponent::EParseResult parseResult = userInputComponent.ParseUserSelectedDices(userInput, selectedDices);
    EXPECT_EQ(parseResult, UserInputComponent::EParseResult::OK);

    std::vector<int> expectedOutput{1, 2, 3};
    EXPECT_EQ(selectedDices, expectedOutput);
}

TEST(TestUserInput, BadInput) {
    UserInputComponent userInputComponent;
    const std::string userInput{"1 a 3"};
    std::vector<int> selectedDices;

    UserInputComponent::EParseResult parseResult = userInputComponent.ParseUserSelectedDices(userInput, selectedDices);
    EXPECT_EQ(parseResult, UserInputComponent::EParseResult::NonDigitInput);

    EXPECT_TRUE(selectedDices.empty());
}

TEST(TestUserInput, TooMuchInput) {
    UserInputComponent userInputComponent;
    const std::string userInput{"1 2 3 4 5 6 7"};
    std::vector<int> selectedDices;

    UserInputComponent::EParseResult parseResult = userInputComponent.ParseUserSelectedDices(userInput, selectedDices);
    EXPECT_EQ(parseResult, UserInputComponent::EParseResult::TooMuchInput);

    EXPECT_TRUE(selectedDices.empty());
}
