#pragma once
#include "TokenType.hpp"
#include <string>

namespace rhayader {
    struct Token {
        TokenType type;
        std::string value;
        unsigned int line;
        
        Token(TokenType type, std::string&& value, unsigned int line);
        Token(const Token& other) = default;
        Token(Token&& other) noexcept;

        Token& operator=(const Token& t) = default;

        bool isEmpty() const;
        void clear(unsigned int lineNumber);
    };
}
