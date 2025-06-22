#pragma once
#include "IExpression.h"
#include <memory>

class BinaryExpression final : public IExpression {
    const char operation;
    const std::shared_ptr<IExpression> expr1;
    const std::shared_ptr<IExpression> expr2;

public:
    BinaryExpression(
        char operation,
        std::shared_ptr<IExpression> expr1,
        std::shared_ptr<IExpression> expr2
    );

    virtual double eval() const override;
    virtual std::string toString() const override;
};