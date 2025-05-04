#pragma once

struct Dice {
public:
    void Roll();

    int GetValue() const;

private:
    int CurrentValue = 0;
};
