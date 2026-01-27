#include <iostream>
#include <cassert>

#include "../tokenizer/Tokenizer.hpp"
#include "../parser/Parser.hpp"
#include "../evaluator/evaluator.hpp"
#include "../evaluator/valueCast.hpp"
#include "../evaluator/Thread.hpp"

void test_adds_two_numbers() {
    std::cout << "Running test: Adds two numbers" << std::endl;
    rhayader::Tokenizer tokenizer;
    tokenizer.tokenize("2 + 2");

    rhayader::Parser parser{ tokenizer.getTokens() };
    const auto tree = parser.parse();

    rhayader::Thread t;
    const auto value = t.evaluator->evaluate(tree);

    assert(rhayader::valueCast<rhayader::NumberValue>(value)->value == 4);
    std::cout << "Test passed!" << std::endl;
}

int main() {
    test_adds_two_numbers();
    return 0;
}
