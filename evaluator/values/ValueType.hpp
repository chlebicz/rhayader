#pragma once
#include <string>
#include <string_view>

namespace rhayader {
    enum class ValueType {
        NumberValue,
        BooleanValue,
        StringValue,
        FunctionValue,
        ExplicitReturnValue,
        ArrayValue,
        MapValue,
        RangeValue,
        NullValue,
        ModuleValue
    };

    std::string_view dumpValueType(const ValueType type);
}
