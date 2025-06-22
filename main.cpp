#include <iostream>

#include "Lexer.h"
#include "Parser.h"
#include <cmath>
#include <iomanip>

using namespace std;

struct TestCase {
    std::string input;
    double expected;
};

void runTests() {
    std::vector<TestCase> tests = {
        {"pi + 2", 5.14},
        {"lang_constant", 228},
        {"2 + 3 * 4", 14},
        {"2 * 3 + 4", 10},
        {"10 / 2 * 3", 15},
        {"12 - 3 - 4", 5},
        {"2 + 3 * 4 - 5 / 2", 11.5},
        {"3 * (4 + 5)", 27},
        {"(2 + 3) * (4 - 1)", 15},
        {"10 / (2 + 3) * 4", 8},
        {"-5 * 3", -15},
        {"7 * -2", -14},
        {"+3 + -4", -1},
        {"--5", 5},
        {"++5", 5},
        {"2 * -(-3)", 6},
        {"-(3 * 4) / -2", 6},
        {"2 * (3 + 4 * (5 - 2))", 30},
        {"((2 + 3) * 4) - (5 / (1 - 0.5))", 10},
        {"1 + (2 * (3 + (4 * (5 - 1))))", 39},
        {"1 / 2 * 3 + 4", 5.5},
        {"3.5 * (2 + 1.5)", 12.25},
        {"0 * 1000", 0},
        {"0 + 0 - 0", 0},
        {"1 + 2 + 3 + 4 + 5", 15},
        {"1 - 2 - 3 - 4", -8},
        {"2 * 3 * 4 * 5", 120},
        {"100 / 2 / 2 / 5", 5},
        {"-(-3 * +4) / -(2 * -3) * -1", -2},
        {"2 * (3 + -(4 - 5) * 2)", 10},
        {"(1.5 + 2.5) * (0 - (3.0 * -2))", 24},
        {"0.5 + 0.5", 1}
    };
    /*
FAIL: 'pi + 2' - expected 5.14, got 5.14159
FAIL: '--5' - exception: Unknown expression
FAIL: '++5' - exception: Unknown expression

Test results: 29 passed, 3 failed
    */

    const double EPSILON = 1e-9;
    int passed = 0;
    int failed = 0;

    for (const auto& test : tests) {
        try {
            auto tokens = Lexer(test.input).tokenize();
            auto expressions = Parser(tokens).parse();

            if (expressions.empty()) {
                std::cerr << "FAIL: '" << test.input
                          << "' - no expression parsed\n";
                failed++;
                continue;
            }

            double result = expressions[0]->eval();

            if (std::abs(result - test.expected) > EPSILON) {
                std::cerr << "FAIL: '" << test.input << "' - expected "
                          << test.expected << ", got " << result << "\n";
                failed++;
            }
            else {
                passed++;
            }
        } catch (const char* e) {
            std::cerr << "FAIL: '" << test.input << "' - exception: " << e
                      << "\n";
            failed++;
        } catch (...) {
            std::cerr << "FAIL: '" << test.input << "' - unknown exception\n";
            failed++;
        }
    }

    if (failed == 0) {
        std::cout << "All " << passed << " tests passed successfully!\n";
    }
    else {
        std::cerr << "\nTest results: " << passed << " passed, " << failed
                  << " failed\n";
    }
}

int main() {
    runTests();
    return 0;
}