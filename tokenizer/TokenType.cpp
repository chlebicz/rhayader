#include "TokenType.hpp"

namespace rhayader {
	std::string dumpTokenType(const TokenType type) {
		switch (type) {
			#define X(tokenType) case TokenType::tokenType: return #tokenType;
			TOKENTYPES
			#undef X
			default:
				throw ParseError("Unknown error");
		}
	}
}