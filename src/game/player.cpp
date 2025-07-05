#include "common/exceptions.hpp"
#include <game/player.hpp>

Player::Player() {
    for (int i = 0; i < Dices_.size(); ++i) {
        Dices_[i].SetID(i + 1);
    }
}

void Player::RollDices() {
    for (auto& dice : Dices_) {
        if (StashedDices_.contains(dice.GetID())) {
            continue;
        }

        dice.Roll();
    }
}

void Player::UpdateStashedDices(const std::vector<int>& stashedIndices) {
    StashedDices_.insert(stashedIndices.begin(), stashedIndices.end());

    if (StashedDices_.size() == 6) {
        StashedDices_.clear();
    }
}

std::vector<std::pair<int, int>> Player::GetDicesState() const {
    std::vector<std::pair<int, int>> dicesState;

    for (const auto& dice : Dices_) {
        if (StashedDices_.contains(dice.GetID())) {
            continue;
        }

        dicesState.push_back({dice.GetID(), dice.GetValue()});
    }

    return dicesState;
}

std::vector<int> Player::SelectDices(std::vector<int> selection) const {
    std::vector<int> selectedDices;
    selectedDices.reserve(selection.size());

    for (const auto i : selection) {
        auto it = std::find_if(Dices_.begin(), Dices_.end(), [i](Dice d) {
            return d.GetID() == i;
        });

        if (it == Dices_.end()) {
            throw CoreGameFailure{"Selected dice ID which is not present"};
        }

        selectedDices.push_back(it->GetValue());
    }

    return selectedDices;
}
