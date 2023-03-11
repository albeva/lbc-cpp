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
    "["sv,
    "]"sv,
    ","sv,
    "="sv,
    // control Keywords
    "AS"sv,
    "DDECLARE"sv,
    "END"sv,
    "EXTERN"sv,
    "FUNCTION"sv,
    "IMPORT"sv,
    "SUB"sv,
    // type keywords
    "INTEGER"sv,
    "ZSTRING"sv
};

const std::unordered_map<std::string_view, TokenKind> pKeywords {
    // keywords
    { "AS"sv, TokenKind::KwAs },
    { "DECLARE"sv, TokenKind::KwDeclare },
    { "END"sv, TokenKind::KwEnd },
    { "EXTERN"sv, TokenKind::KwExtern },
    { "FUNCTION"sv, TokenKind::KwFunction },
    { "IMPORT"sv, TokenKind::KwImport },
    { "SUB"sv, TokenKind::KwSub },
    // types
    { "INTEGER"sv, TokenKind::TyInteger },
    { "ZSTRING"sv, TokenKind::TyZString },
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
