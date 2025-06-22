#include "NumberExpression.h"

NumberExpression::NumberExpression(double value) : value(value) {
}

double NumberExpression::eval() const {
    return this->value;
}

std::string NumberExpression::toString() const {
    return std::to_string(this->value);
}