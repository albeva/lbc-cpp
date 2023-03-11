//
// Created by Albert on 11/03/2023.
//
#pragma once
#include "pch.hpp"

namespace lbc {
[[noreturn]] void fatalError(const std::string& message, bool prefix = true);
} // namespace lbc
