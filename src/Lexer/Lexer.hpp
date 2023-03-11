//
// Created by Albert on 04/03/2023.
//
#pragma once
#include "pch.hpp"
#include "Token.hpp"
namespace lbc {
class Context;
class Source;
class Token;

class Lexer final {
public:
    explicit Lexer(Source* source, Context* context);
    void next(Token& token);

private:
    void skipUntilLineEnd();
    void make(Token& token, TokenKind kind, size_t len = 1);
    void string(Token& token);
    void identifier(Token& token);
    void number(Token& token);
    void fileEnd(Token& token);
    void invalid(Token& token);

    [[nodiscard]] SourceLoc loc(const char* start) const;

    Source* m_source;
    Context* m_context;
    const char* m_input;
    bool m_emitEndOfStmt;
};

} // namespace lbc
