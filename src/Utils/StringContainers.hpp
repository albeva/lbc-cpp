//
// Created by Albert on 11/03/2023.
//
#pragma once
#include "pch.hpp"

namespace lbc {
namespace containers {
    struct HeterogeneousHash {
        using is_transparent = void;
        [[nodiscard]] size_t operator()(const char* txt) const
        {
            return std::hash<std::string_view> {}(txt);
        }
        [[nodiscard]] size_t operator()(std::string_view txt) const
        {
            return std::hash<std::string_view> {}(txt);
        }
        [[nodiscard]] size_t operator()(const std::string& txt) const
        {
            return std::hash<std::string> {}(txt);
        }
    };
} // namespace containers

using StringSet = std::unordered_set<std::string, containers::HeterogeneousHash, std::equal_to<>>;

template <typename T>
using StringMap = std::unordered_map<std::string, T, StringSet, std::equal_to<>>;
} // namespace lbc
