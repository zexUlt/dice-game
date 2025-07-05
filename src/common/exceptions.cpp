#include "common/exceptions.hpp"

BaseException::BaseException(std::string msg) noexcept
    : Message_(std::move(msg)) {
}

const char* BaseException::what() const noexcept {
    return Message_.c_str();
}

UserInputException::UserInputException(std::string msg) noexcept
    : BaseException(std::move(msg)) {
}

CoreGameFailure::CoreGameFailure(std::string msg) noexcept
    : BaseException(std::move(msg)) {
}
