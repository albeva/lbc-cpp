//
// Created by Albert on 11/03/2023.
//
#pragma once
#include "Driver/SourceLoc.hpp"
#include "pch.hpp"
namespace lbc {

enum class TokenKind : unsigned {
    // basic
    Invalid,
    EndOfStmt,
    EndOfFile,
    // literals
    IntegerLiteral,
    FloatingPointLiteral,
    StringLiteral,
    BooleanLiteral,
    NullLiteral,
    Identifier,
    // operators
    ParenOpen,
    ParenClose,
    Comma,
    // control Keywords
    KwImport,
    KwDeclare,
    KwSub,
    KwFunction,
    KwAs,
    // type keywords
    TyInteger,
    TyString
};

class Token final {
public:
    using Value = std::variant<std::monostate, std::string_view, double, uint64_t, bool>;

    void set(TokenKind kind, SourceLoc loc, Value value = std::monostate {})
    {
        m_kind = kind;
        m_loc = loc;
        m_value = value;
    }

    [[nodiscard]] TokenKind getKind() const
    {
        return m_kind;
    }

    [[nodiscard]] SourceLoc getLoc() const
    {
        return m_loc;
    }

    [[nodiscard]] const Value& getValue() const
    {
        return m_value;
    }

    [[nodiscard]] bool is(TokenKind kind) const
    {
        return m_kind == kind;
    }

    template <typename... Ts>
    [[nodiscard]] bool is(TokenKind kind, Ts... rest) const
    {
        return is(kind) || is(rest...);
    }

    [[nodiscard]] bool isNot(TokenKind kind) const
    {
        return m_kind != kind;
    }

    template <typename... Ts>
    [[nodiscard]] bool isNot(TokenKind kind, Ts... rest) const
    {
        return isNot(kind) && isNot(rest...);
    }

    [[nodiscard]] std::string_view description() const { return description(m_kind); }

    [[nodiscard]] static std::string_view description(TokenKind kind);

    [[nodiscard]] static TokenKind findKind(std::string_view ident);

private:
    TokenKind m_kind {};
    SourceLoc m_loc {};
    Value m_value {};
};

}