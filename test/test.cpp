#ifdef RUN_TESTS
#include <catch.hpp>

#include "../tokenizer/Tokenizer.hpp"
#include "../parser/Parser.hpp"
#include "../evaluator/evaluator.hpp"
#include "../evaluator/valueCast.hpp"
#include "../evaluator/Thread.hpp"

TEST_CASE("Adds two numbers") {
    soviet::Tokenizer tokenizer;
    tokenizer.tokenize("2 + 2");

    soviet::Parser parser{ tokenizer.getTokens() };
    const auto tree = parser.parse();

    soviet::Thread t;
    const auto value = t.evaluator->evaluate(tree);

    REQUIRE(valueCast<soviet::NumberValue>(value)->value == 4);
}
#endif