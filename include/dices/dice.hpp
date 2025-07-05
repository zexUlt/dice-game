#pragma once

struct Dice {
public:
    void Roll();

    int GetValue() const;
    void SetID(int newId);
    int GetID() const;

private:
    int CurrentValue = 0;
    int ID = -1;
};
