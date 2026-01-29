#include "ValueType.hpp"

namespace rhayader {
	std::string dumpValueType(const ValueType type) {
		switch (type) {
			case ValueType::ArrayValue: return "array";
			case ValueType::BooleanValue: return "boolean";
			case ValueType::ExplicitReturnValue: return "explicit_return_value";
			case ValueType::FunctionValue: return "function";
			case ValueType::NumberValue: return "number";
			case ValueType::StringValue: return "string";
			case ValueType::MapValue: return "map";
			case ValueType::RangeValue: return "range";
			case ValueType::NullValue: return "null";
			case ValueType::ModuleValue: return "module";
		}
		return "wtf";
	}
}