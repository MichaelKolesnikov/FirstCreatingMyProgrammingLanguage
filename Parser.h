#pragma once

#include "Token.h"
#include "ast/IExpression.h"
#include <memory>
#include <vector>

class Parser {
private:
    static const Token END_OF_FILE;

    const std::vector<Token> tokens;
    const int size;

    int currentTokenNumber;

    Token get(int relativePosition);

    bool match(TokenType tokenType);

    std::shared_ptr<IExpression> primary();
    std::shared_ptr<IExpression> unary();
    std::shared_ptr<IExpression> multiplicative();
    std::shared_ptr<IExpression> additive();
    std::shared_ptr<IExpression> expression();

public:
    Parser(const std::vector<Token>& tokens);

    std::vector<std::shared_ptr<IExpression>> parse();
};