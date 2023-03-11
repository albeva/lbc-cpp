//
// Created by Albert on 04/03/2023.
//
#include "Driver/Context.hpp"
#include "Driver/Source.hpp"
#include "Lexer/Lexer.hpp"
#include "Lexer/Token.hpp"
using namespace lbc;

int main(int /* argc */, const char** /* argv */)
{
    try {
        Source src { "../samples/Hello.bas" };
        Context ctx;
        Lexer lexer { &src, &ctx };

        Token token;
        do {
            lexer.next(token);
            std::cout << token.description() << '\n';
        } while (token.isNot(TokenKind::EndOfFile));

        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "lbc error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}
