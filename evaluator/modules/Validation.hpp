#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../values/Value.hpp"
#include "../values/ValueType.hpp"

namespace rhayader {
    void validateArgumentCount(const std::string& funcName, size_t count, size_t expected);
    void validateArgumentCount(const std::string& funcName, size_t count, size_t min, size_t max);
    void validateArgumentType(const std::string& funcName, size_t index, const std::shared_ptr<Value>& arg, ValueType expected);
    void validateArgumentType(const std::string& funcName, size_t index, const std::shared_ptr<Value>& arg, const std::vector<ValueType>& expectedTypes);
}
