//
// Created by Albert on 11/03/2023.
//
#include "Source.hpp"
using namespace lbc;

Source::Source(const fs::path& path)
    : m_name { path.string() }
{
    if (!fs::exists(path)) {
        throw SourceException("File '" + m_name + "' not found");
    }

    std::ifstream file { path, std::ios::binary | std::ios::in };
    if (!file.is_open()) {
        throw SourceException("Failed to open '"s + m_name + "'");
    }

    m_source = std::string { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
}

Source::Source(std::string name, std::string source)
    : m_name { std::move(name) }
    , m_source { std::move(source) }
{
}
