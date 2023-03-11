//
// Created by Albert on 04/03/2023.
//
#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <charconv>
#include <concepts>
#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <optional>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <variant>
#include <vector>

namespace lbc {
namespace fs = std::filesystem;
namespace ranges = std::ranges;
using namespace std::literals;
} // namespace lbc

// global lbc headers
#include "Utils/Error.hpp"
#include "Utils/StringContainers.hpp"
