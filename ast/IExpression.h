#pragma once
#include <string>

class IExpression {
public:
    virtual double eval() const = 0;
    virtual std::string toString() const = 0;
};