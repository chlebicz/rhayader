#pragma once
#include <string>
#include <stdexcept>
#include "../parser/ParseError.hpp"

#define TOKENTYPES \
    X(none) \
    X(unknown) \
    X(undefined) \
    X(name) \
    X(number) \
    X(string) \
    X(add_op) \
    X(sub_op) \
    X(div_op) \
    X(mul_op) \
    X(open_bracket) \
    X(close_bracket) \
    X(equals_op) \
    X(double_equals_op) \
    X(not_equals_op) \
    X(comma) \
    X(arrow) \
    X(greater_than) \
    X(open_curly_bracket) \
    X(close_curly_bracket) \
    X(dot) \
    X(comment) \
    X(negation) \
    X(less_than_op) \
    X(greater_than_or_equal_op) \
    X(less_than_or_equal_op) \
    X(open_square_bracket) \
    X(close_square_bracket) \
    X(colon) \
    X(or_op) \
    X(and_op) \
    X(pipe_op)

namespace rhayader {
    enum class TokenType {
        #define X(tokenType) tokenType,
        TOKENTYPES
        #undef X
    };

    std::string dumpTokenType(const TokenType type);
}
