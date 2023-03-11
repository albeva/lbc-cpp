//
// Created by Albert on 04/03/2023.
//
#pragma once
#include "Token.hpp"
#include "pch.hpp"
namespace lbc {
class Context;
class Source;
class Token;

class Lexer final {
public:
    explicit Lexer(Source* source, Context* context);
    void next(Token& token);

private:
    void make(Token& token, TokenKind kind, size_t len = 1);
    void string(Token& token);
    void identifier(Token& token);

    void skipUntilLineEnd();
    [[nodiscard]] SourceLoc loc(const char* start) const;

    Source* m_source;
    Context* m_context;
    const char* m_input;
    bool m_emitEndOfStmt;
    void number(Token& token);
};

} // namespace lbc
