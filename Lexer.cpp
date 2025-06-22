#include "Lexer.h"

const std::string Lexer::OPERATOR_CHARS = "+-*/()";
const TokenType Lexer::OPERATOR_TOKENS[] = {
    TokenType::PLUS,
    TokenType::MINUS,
    TokenType::STAR,
    TokenType::SLASH,
    TokenType::LPAREN,
    TokenType::RPAREN
};

Lexer::Lexer(const std::string& input) :
    input(input), length(input.size()), currentPosition(0) {
}

void Lexer::addToken(TokenType tokenType, const std::string& text) {
    this->tokens.push_back(Token(tokenType, text));
}

void Lexer::addToken(TokenType tokenType) {
    this->addToken(tokenType, "");
}

char Lexer::peek(int relativePosition) {
    const int position = this->currentPosition + relativePosition;

    if (position >= this->length) {
        return '\0';
    }

    return this->input[position];
}

char Lexer::next() {
    ++this->currentPosition;
    return this->getCurrentChar();
}

char Lexer::getCurrentChar() const {
    return this->input[this->currentPosition];
}

void Lexer::tokenizeNumber() {
    std::string buffer;
    char currentChar = this->getCurrentChar();
    while (true) {
        if (currentChar == '.') {
            if (buffer.contains('.')) {
                throw "Invalid float number";
            }
        }
        else if (!('0' <= currentChar && currentChar <= '9')) {
            break;
        }
        buffer.push_back(currentChar);
        currentChar = this->next();
    }
    this->addToken(TokenType::NUMBER, buffer);
}

void Lexer::tokenizeWord() {
    std::string buffer;
    char currentChar = this->getCurrentChar();
    while (true) {
        if (!('0' <= currentChar && currentChar <= '9')
            && !(
                'a' <= currentChar && currentChar <= 'z'
                || 'A' <= currentChar && currentChar <= 'Z'
            )
            && currentChar != '_') {
            break;
        }
        buffer.push_back(currentChar);
        currentChar = this->next();
    }
    this->addToken(TokenType::WORD, buffer);
}

void Lexer::tokenizeOperator() {
    const int operatorNumber = OPERATOR_CHARS.find(this->getCurrentChar());
    this->addToken(Lexer::OPERATOR_TOKENS[operatorNumber]);
    this->next();
}

std::vector<Token> Lexer::tokenize() {
    while (this->currentPosition < this->length) {
        const char currentChar = this->getCurrentChar();

        if ('0' <= currentChar && currentChar <= '9') {
            this->tokenizeNumber();
        }
        else if ('a' <= currentChar && currentChar <= 'z'
                 || 'A' <= currentChar && currentChar <= 'Z') {
            this->tokenizeWord();
        }
        else if (this->OPERATOR_CHARS.find(currentChar) != std::string::npos) {
            this->tokenizeOperator();
        }
        else {
            this->next();
        }
    }
    return this->tokens;
}