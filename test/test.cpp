#include <catch2/catch_test_macros.hpp>

#include "../tokenizer/Tokenizer.hpp"
#include "../parser/Parser.hpp"
#include "../evaluator/evaluator.hpp"
#include "../evaluator/valueCast.hpp"
#include "../evaluator/Thread.hpp"
#include "../evaluator/values/NumberValue.hpp"

TEST_CASE("Adds two numbers") {
    rhayader::Tokenizer tokenizer;
    tokenizer.tokenize("2 + 2");

    rhayader::Parser parser{ tokenizer.getTokens() };
    const auto tree = parser.parse();

    rhayader::Thread t;
    const auto value = t.evaluator->evaluate(tree);

    REQUIRE(rhayader::valueCast<rhayader::NumberValue>(value)->value == 4);
}

TEST_CASE("Function definition and call") {
    rhayader::Tokenizer tokenizer;
    // ((x) -> x * x)(5)
    tokenizer.tokenize("((x) -> x * x)(5)");

    rhayader::Parser parser{ tokenizer.getTokens() };
    const auto tree = parser.parse();

    rhayader::Thread t;
    const auto value = t.evaluator->evaluate(tree);

    REQUIRE(rhayader::valueCast<rhayader::NumberValue>(value)->value == 25);
}

TEST_CASE("Math module usage") {
    rhayader::Tokenizer tokenizer;
    // Math.max([10, 20]) - Math.max expects an array
    tokenizer.tokenize("Math.max([10, 20])");

    rhayader::Parser parser{ tokenizer.getTokens() };
    const auto tree = parser.parse();

    rhayader::Thread t;
    const auto value = t.evaluator->evaluate(tree);

    REQUIRE(rhayader::valueCast<rhayader::NumberValue>(value)->value == 20);
}

TEST_CASE("String module usage") {
    rhayader::Tokenizer tokenizer;
    // String.length("test")
    tokenizer.tokenize("String.length(\"test\")");

    rhayader::Parser parser{ tokenizer.getTokens() };
    const auto tree = parser.parse();

    rhayader::Thread t;
    const auto value = t.evaluator->evaluate(tree);

    REQUIRE(rhayader::valueCast<rhayader::NumberValue>(value)->value == 4);
}

TEST_CASE("Array module usage") {
    rhayader::Tokenizer tokenizer;
    // Array.length([1, 2])
    tokenizer.tokenize("Array.length([1, 2])");

    rhayader::Parser parser{ tokenizer.getTokens() };
    const auto tree = parser.parse();

    rhayader::Thread t;
    const auto value = t.evaluator->evaluate(tree);

    REQUIRE(rhayader::valueCast<rhayader::NumberValue>(value)->value == 2);
}
