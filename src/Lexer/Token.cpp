//
// Created by Albert on 11/03/2023.
//
#include "Token.hpp"
using namespace lbc;

namespace {
constexpr std::array kTokens {
    // basic
    "<Invalid>"sv,
    "<End-Of-Stmt>"sv,
    "<End-Of-File>"sv,
    // literals
    "<Integer-Literal>"sv,
    "<FloatingPoint-Literal>"sv,
    "<String-Literal>"sv,
    "<Boolean-Literal>"sv,
    "<Null-Literal>"sv,
    "<Identifier>"sv,
    // operators
    "("sv,
    ")"sv,
    ","sv,
    // control Keywords
    "IMPORT"sv,
    "DECLARE"sv,
    "SUB"sv,
    "FUNCTION"sv,
    "AS"sv,
    // type keywords
    "INTEGER"sv,
    "STRING"sv
};

const std::unordered_map<std::string_view, TokenKind> pKeywords {
    { "IMPORT"sv, TokenKind::KwImport },
    { "DECLARE"sv, TokenKind::KwDeclare },
    { "SUB"sv, TokenKind::KwSub },
    { "FUNCTION"sv, TokenKind::KwFunction },
    { "INTEGER"sv, TokenKind::TyInteger },
    { "STRING"sv, TokenKind::TyString },
};
}

std::string_view Token::description(TokenKind kind)
{
    return kTokens.at(static_cast<size_t>(kind));
}

TokenKind Token::findKind(std::string_view ident)
{
    auto iter = pKeywords.find(ident);
    if (iter != pKeywords.end()) {
        return iter->second;
    }
    return TokenKind::Identifier;
}
