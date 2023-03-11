//
// Created by Albert on 04/03/2023.
//
#include "Lexer.hpp"
#include "Driver/Context.hpp"
#include "Driver/Source.hpp"
#include "Token.hpp"
using namespace lbc;

namespace {
inline bool isLineOrFileEnd(char ch)
{
    return ch == '\n' || ch == '\r' || ch == '\0';
}

inline bool isAlpha(char ch)
{
    return (ch >= 'a' && ch <= 'z')
        || (ch >= 'A' && ch <= 'Z');
}

inline bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

inline bool isIdentChar(char ch)
{
    return isAlpha(ch) || ch == '_' || isDigit(ch);
}

inline char toUpper(char x)
{
    if (x >= 'a' && x <= 'z') {
        return x - 'a' + 'A'; // NOLINT
    }
    return x;
}
}

Lexer::Lexer(Source* source, Context* context)
    : m_source(source)
    , m_context(context)
    , m_input(source->source())
    , m_emitEndOfStmt(false)
{
}

void Lexer::next(Token& token)
{
    size_t len = 1;
    while (true) {
        auto ch = *m_input;
        switch (ch) {
        case '\0':
            return fileEnd(token);
        case ' ':
        case '\t':
            m_input++;
            continue;
        case '\r':
            if (m_input[1] == '\n') {
                len++;
            }
            [[fallthrough]];
        case '\n':
            if (m_emitEndOfStmt) {
                return make(token, TokenKind::EndOfStmt, len);
            }
            std::advance(m_input, len);
            len = 1;
            continue;
        case '\'':
            m_input++;
            skipUntilLineEnd();
            continue;
        case '"':
            return string(token);
        case '(':
            return make(token, TokenKind::ParenOpen);
        case ')':
            return make(token, TokenKind::ParenClose);
        case ',':
            return make(token, TokenKind::Comma);
        default:
            if (isAlpha(ch)) {
                return identifier(token);
            }

            if (isDigit(ch)) {
                return number(token);
            }

            return invalid(token);
        }
    }
}

void Lexer::skipUntilLineEnd()
{
    while (!isLineOrFileEnd(*m_input)) {
        m_input++;
    }
}

void Lexer::make(Token& token, TokenKind kind, size_t len)
{
    m_emitEndOfStmt = kind != TokenKind::EndOfStmt;

    const auto* start = m_input;
    std::advance(m_input, len);
    token.set(kind, loc(start));
}

void Lexer::string(Token& token)
{
    m_emitEndOfStmt = true;

    const auto* start = m_input++;
    while (true) {
        auto cur = *m_input;
        if (isLineOrFileEnd(cur)) {
            fatalError("FIXME: handle unterminated string");
        }
        m_input++;

        if (cur == '\"') {
            break;
        }
    }

    token.set(TokenKind::StringLiteral, loc(start), std::string_view { start + 1, m_input - 1 });
}

void Lexer::identifier(Token& token)
{
    m_emitEndOfStmt = true;

    const auto* start = m_input++;
    while (isIdentChar(*m_input)) {
        m_input++;
    }

    std::string upppercased;
    upppercased.reserve(static_cast<size_t>(std::distance(start, m_input)));
    std::transform(start, m_input, std::back_inserter(upppercased), toUpper);

    if (upppercased == "REM"sv) {
        skipUntilLineEnd();
        return next(token);
    }

    auto kind = Token::findKind(upppercased);
    switch (kind) {
    case TokenKind::Identifier:
        token.set(kind, loc(start), m_context->retainUniqueCopy(upppercased));
        break;
    default:
        token.set(kind, loc(start));
    }
}

void Lexer::number(Token& token)
{
    m_emitEndOfStmt = true;

    const auto* start = m_input++;
    while (isDigit(*m_input)) {
        m_input++;
    }

    uint64_t value {};
    if (std::from_chars(start, m_input, value).ec != std::errc()) {
        fatalError("FIXME: handle invalid integers");
    }
    token.set(TokenKind::IntegerLiteral, loc(start), value);
}

void Lexer::fileEnd(Token& token)
{
    if (m_emitEndOfStmt) {
        return make(token, TokenKind::EndOfStmt, 0);
    }
    return make(token, TokenKind::EndOfFile, 0);
}

void Lexer::invalid(Token& token)
{
    const auto* start = m_input;
    m_input++;
    token.set(TokenKind::Invalid, loc(start));
}

SourceLoc Lexer::loc(const char* start) const
{
    return {
        .start = static_cast<unsigned>(std::distance(m_source->source(), start)),
        .end = static_cast<unsigned>(std::distance(m_source->source(), m_input))
    };
}
