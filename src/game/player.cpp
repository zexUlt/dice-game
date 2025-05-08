#include "dices/dice.hpp"

#include <algorithm>
#include <game/player.hpp>

void Player::RollDices() {
    for (auto& dice : Dices_) {
        dice.Roll();
    }
}

std::array<int, 6> Player::GetDicesState() const {
    std::array<int, 6> dicesState;

    std::transform(Dices_.begin(), Dices_.end(), dicesState.begin(), [](const auto& dice) {
        return dice.GetValue();
    });

    return dicesState;
}

std::vector<int> Player::SelectDices(std::vector<int> selection) const {
    std::vector<int> selectedDices;
    selectedDices.reserve(selection.size());

    for (int i = 0; i < selection.size(); ++i) {
        selectedDices.push_back(Dices_[i].GetValue());
    }

    return selectedDices;
}
