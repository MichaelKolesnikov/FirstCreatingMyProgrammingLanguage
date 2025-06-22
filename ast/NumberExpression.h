#pragma once
#include "IExpression.h"

class NumberExpression final : public IExpression {
    const double value;

public:
    NumberExpression(double value);

    virtual double eval() const override;
    virtual std::string toString() const override;
};