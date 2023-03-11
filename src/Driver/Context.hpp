//
// Created by Albert on 11/03/2023.
//
#pragma once
#include "pch.hpp"
namespace lbc {

class Context final {
public:
    [[nodiscard]] std::string_view retainUniqueCopy(std::string_view str);

private:
    StringSet m_stringStore {};
};

} // namespace lbc
