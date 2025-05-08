#pragma once

#include <exception>

class UserInputException : public std::exception {
public:
    using std::exception::exception;
};
