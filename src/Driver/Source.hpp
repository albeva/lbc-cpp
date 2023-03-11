//
// Created by Albert on 11/03/2023.
//
#pragma once
#include "SourceLoc.hpp"
#include "pch.hpp"
namespace lbc {

class SourceException final : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class Source final {
public:
    explicit Source(const fs::path& path);
    Source(std::string name, std::string source);

    [[nodiscard]] std::string_view name() const { return m_name; }
    [[nodiscard]] const char* source() const { return m_source.data(); }

private:
    std::string m_name;
    std::string m_source;
};

} // namespace lbc