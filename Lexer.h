#pragma once

#include <vector>

#include "Token.h"

class Lexer {
    static const std::string OPERATOR_CHARS;
    static const TokenType OPERATOR_TOKENS[];

    const std::string input;
    const int length;
    std::vector<Token> tokens;

    int currentPosition;

    void addToken(TokenType tokenType, const std::string& text);
    void addToken(TokenType tokenTYpe);

    char peek(int relativePosition);

    char next();

    char getCurrentChar() const;

    void tokenizeNumber();
    void tokenizeWord();
    void tokenizeOperator();

public:
    Lexer(const std::string& input);

    std::vector<Token> tokenize();
};