#include "Token.hpp"
#include <utility>

namespace rhayader {
	Token::Token(Token&& other) noexcept
		: type(std::exchange(other.type, TokenType::undefined)),
		  value(std::move(other.value)),
		  line(std::exchange(other.line, 0))
	{}

	Token::Token(TokenType type, std::string&& value, unsigned int line)
		: type(type), value(std::move(value)), line(line)
	{}

	bool Token::isEmpty() const {
		return this->type == TokenType::none;
	}

	void Token::clear(unsigned int lineNumber) {
		this->type = TokenType::none;
		this->value = "";
		this->line = lineNumber;
	}
}
