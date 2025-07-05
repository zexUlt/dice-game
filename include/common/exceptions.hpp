#pragma once

#include <exception>
#include <string>
#include <string_view>

class BaseException : public std::exception {
public:
    BaseException(std::string msg) noexcept;
    virtual ~BaseException() = default;

    const char* what() const noexcept override;

private:
    std::string Message_;
};

class UserInputException : public BaseException {
public:
    UserInputException(std::string msg) noexcept;
    ~UserInputException() = default;
};

class CoreGameFailure : public BaseException {
public:
    CoreGameFailure(std::string msg) noexcept;

    ~CoreGameFailure() = default;
};
