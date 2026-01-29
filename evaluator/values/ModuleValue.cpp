#include "ModuleValue.hpp"
#include "../valueCast.hpp"
#include "NullValue.hpp"

namespace rhayader {
	ModuleValue::ModuleValue(Evaluator& evaluator)
		: Value{ValueType::ModuleValue}, evaluator(evaluator) {}

	ModuleValue::ModuleValue(Evaluator& evaluator, std::string name)
		: Value{ValueType::ModuleValue}, evaluator(evaluator), name(std::move(name)) {}

	ModuleValue::ModuleValue(Evaluator& evaluator, std::string name, std::unordered_map<std::string, std::shared_ptr<Value>> variables)
		: Value{ValueType::ModuleValue}, name(std::move(name)), evaluator(evaluator), variables(std::move(variables)) {}

	bool ModuleValue::equals(const std::shared_ptr<Value>& other) {
		return other->type == ValueType::ModuleValue && valueCast<ModuleValue>(other).get() == this;
	}

	std::shared_ptr<Value> ModuleValue::clone() {
		auto result = std::make_shared<ModuleValue>(evaluator);
		for (const auto& [key, value] : variables)
			result->variables[key] = value->clone();
		return result;
	}

	std::string ModuleValue::dump() const {
		return name;
	}

	std::shared_ptr<Value> ModuleValue::get(const std::string& prop) {
		auto result = variables.find(prop);
		if (result == variables.end())
			return std::make_shared<NullValue>();
		return result->second;
	}
}