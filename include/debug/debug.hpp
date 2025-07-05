#pragma once

#include <iostream>

#define LOG_DEBUG_ARRAY(x)          \
    {                               \
        std::cout << "Debug: ";     \
        for (const auto el : x) {   \
            std::cout << el << " "; \
        }                           \
        std::cout << '\n';          \
    }

#define LOG_DEBUG(x) \
    { std::cout << x << '\n'; }