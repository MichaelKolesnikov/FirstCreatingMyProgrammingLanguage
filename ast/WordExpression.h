#pragma once
#include "IExpression.h"
#include <string>
#include <unordered_map>

class WordExpression final : public IExpression {
    static const std::unordered_map<std::string, double> CONSTANTS;

    const std::string name;

public:
    WordExpression(const std::string& name);

    virtual double eval() const override;

    virtual std::string toString() const override;
};