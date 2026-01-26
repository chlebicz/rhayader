#include "Validation.hpp"
#include "../EvaluateError.hpp"

namespace rhayader {
    void validateArgumentCount(const std::string& funcName, size_t count, size_t expected) {
        if (count != expected) {
            throw EvaluateError(funcName + " expects " + std::to_string(expected) + " argument(s)");
        }
    }

    void validateArgumentCount(const std::string& funcName, size_t count, size_t min, size_t max) {
        if (count < min || count > max) {
            throw EvaluateError(funcName + " expects between " + std::to_string(min) + " and " + std::to_string(max) + " arguments");
        }
    }

    void validateArgumentType(const std::string& funcName, size_t index, const std::shared_ptr<Value>& arg, ValueType expected) {
        if (arg->type != expected) {
            throw EvaluateError(funcName + " argument " + std::to_string(index + 1) + " must be of type " + dumpValueType(expected));
        }
    }

    void validateArgumentType(const std::string& funcName, size_t index, const std::shared_ptr<Value>& arg, const std::vector<ValueType>& expectedTypes) {
        bool match = false;
        for (const auto& type : expectedTypes) {
            if (arg->type == type) {
                match = true;
                break;
            }
        }
        if (!match) {
            std::string expectedStr;
            for (size_t i = 0; i < expectedTypes.size(); ++i) {
                expectedStr += dumpValueType(expectedTypes[i]);
                if (i < expectedTypes.size() - 1) expectedStr += " or ";
            }
            throw EvaluateError(funcName + " argument " + std::to_string(index + 1) + " must be one of: " + expectedStr);
        }
    }
}
