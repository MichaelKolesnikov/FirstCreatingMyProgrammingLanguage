#include "Parser.h"
#include "ast/BinaryExpression.h"
#include "ast/NumberExpression.h"
#include "ast/UnaryExpression.h"
#include "ast/WordExpression.h"

const Token Parser::END_OF_FILE = Token(TokenType::END_OF_FILE, "");

Parser::Parser(const std::vector<Token>& tokens) :
    tokens(tokens), size(tokens.size()), currentTokenNumber(0) {
}

Token Parser::get(int relativePosition) {
    const int tokenPosition = this->currentTokenNumber + relativePosition;
    if (tokenPosition >= this->size) {
        return this->END_OF_FILE;
    }
    return this->tokens[tokenPosition];
}

bool Parser::match(TokenType tokenType) {
    const Token currentToken = this->get(0);
    if (tokenType != currentToken.type) {
        return false;
    }
    ++this->currentTokenNumber;
    return true;
}

std::shared_ptr<IExpression> Parser::primary() {
    const Token currentToken = this->get(0);
    if (this->match(TokenType::NUMBER)) {
        return std::make_shared<NumberExpression>(std::stod(currentToken.text));
    }
    if (this->match(TokenType::WORD)) {
        return std::make_shared<WordExpression>(currentToken.text);
    }
    if (this->match(TokenType::LPAREN)) {
        auto result = this->expression();
        this->match(TokenType::RPAREN);
        return result;
    }
    throw "Unknown expression";
}

std::shared_ptr<IExpression> Parser::unary() {
    if (this->match(TokenType::MINUS)) {
        return std::make_shared<UnaryExpression>('-', this->primary());
    }
    if (this->match(TokenType::PLUS)) {
        return std::make_shared<UnaryExpression>('+', this->primary());
    }
    return this->primary();
}

std::shared_ptr<IExpression> Parser::multiplicative() {
    auto result = this->unary();

    while (true) {
        if (this->match(TokenType::STAR)) {
            result = std::make_shared<BinaryExpression>(
                '*', result, this->unary()
            );
            continue;
        }
        if (this->match(TokenType::SLASH)) {
            result = std::make_shared<BinaryExpression>(
                '/', result, this->unary()
            );
            continue;
        }
        break;
    }

    return result;
}
std::shared_ptr<IExpression> Parser::additive() {
    auto result = this->multiplicative();

    while (true) {
        if (this->match(TokenType::PLUS)) {
            result = std::make_shared<BinaryExpression>(
                '+', result, this->multiplicative()
            );
            continue;
        }
        if (this->match(TokenType::MINUS)) {
            result = std::make_shared<BinaryExpression>(
                '-', result, this->multiplicative()
            );
            continue;
        }
        break;
    }

    return result;
}

std::shared_ptr<IExpression> Parser::expression() {
    return this->additive();
}

std::vector<std::shared_ptr<IExpression>> Parser::parse() {
    std::vector<std::shared_ptr<IExpression>> result;

    while (!this->match(TokenType::END_OF_FILE)) {
        result.push_back(this->expression());
    }

    return result;
}