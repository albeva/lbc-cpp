//
// Created by Albert on 11/03/2023.
//
#include "Error.hpp"
using namespace lbc;

void lbc::fatalError(const std::string& message, bool prefix)
{
    if (prefix) {
        std::cerr << "lbc: error: ";
    }
    std::cerr << message << std::endl;
    std::exit(EXIT_FAILURE);
}
