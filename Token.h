#pragma once
#include "TokenType.h"
#include <string>

struct Token {
    TokenType type;
    std::string text;
};