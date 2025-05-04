#pragma once

#include <functional>

namespace std {
    template <>
    struct hash<pair<int, int>> {
        size_t operator()(const pair<int, int>& e) const {
            auto h1 = hash<int>{}(e.first);
            auto h2 = hash<int>{}(e.second);
            return h1 ^ (h2 << 1);
        }
    };
} // namespace std
