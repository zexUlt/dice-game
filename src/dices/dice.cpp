#include "dices/dice.hpp"

#include <random>

void Dice::Roll() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> distribution(1, 6);

    CurrentValue = distribution(rng);
}

int Dice::GetValue() const {
    return CurrentValue;
}

void Dice::SetID(int newId) {
    if (ID != -1) {
        return;
    }

    ID = newId;
}

int Dice::GetID() const {
    return ID;
}