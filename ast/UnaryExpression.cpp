#include "UnaryExpression.h"

UnaryExpression::UnaryExpression(
    char operation,
    std::shared_ptr<IExpression> expr
) : operation(operation), expr(expr) {
}

double UnaryExpression::eval() const {
    switch (this->operation) {
    case '-':
        return -this->expr->eval();
        break;
    case '+':
    default:
        return this->expr->eval();
        break;
    }
}

std::string UnaryExpression::toString() const {
    return this->operation + this->expr->toString();
}