#include "WordExpression.h"
#include <cmath>

const std::unordered_map<std::string, double> WordExpression::CONSTANTS
    = {{"pi", M_PI}, {"e", M_E}, {"phi", 1.61803}, {"lang_constant", 228}};

WordExpression::WordExpression(const std::string& name) : name(name) {
}

double WordExpression::eval() const {
    if (this->CONSTANTS.find(this->name) == std::end(this->CONSTANTS)) {
        throw "Invalid constant name";
    }
    return this->CONSTANTS.at(this->name);
}

std::string WordExpression::toString() const {
    return this->name;
}