#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(
    char operation,
    std::shared_ptr<IExpression> expr1,
    std::shared_ptr<IExpression> expr2
) : operation(operation), expr1(expr1), expr2(expr2) {
}

double BinaryExpression::eval() const {
    switch (operation) {
    case '-':
        return this->expr1->eval() - this->expr2->eval();
        break;
    case '*':
        return this->expr1->eval() * this->expr2->eval();
        break;
    case '/':
        return this->expr1->eval() / this->expr2->eval();
        break;
    case '+':
    default:
        return this->expr1->eval() + this->expr2->eval();
        break;
    }
}

std::string BinaryExpression::toString() const {
    return "(" + this->expr1->toString() + " " + this->operation + " "
        + this->expr2->toString() + ")";
}