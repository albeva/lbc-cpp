//
// Created by Albert on 11/03/2023.
//
#include "Context.hpp"
using namespace lbc;

std::string_view Context::retainUniqueCopy(std::string_view str)
{
    auto iter = m_stringStore.find(str);
    if (iter != m_stringStore.end()) {
        return *iter;
    }
    return *m_stringStore.emplace(str).first;
}
