#pragma once
#include "IExpression.h"
#include <memory>

class UnaryExpression final : public IExpression {
    const char operation;
    const std::shared_ptr<IExpression> expr;

public:
    UnaryExpression(char operation, std::shared_ptr<IExpression> expr);

    virtual double eval() const override;
    virtual std::string toString() const override;
};
