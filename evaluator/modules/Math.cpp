#include "Math.hpp"
#include "../EvaluateError.hpp"
#include "Validation.hpp"
#include <random>
#include <cmath>

namespace rhayader {
    MathModule::MathModule(Evaluator& evaluator) : ModuleValue{evaluator, "Math"} {
        variables["sin"] = std::make_shared<FunctionValue>(&sin);
        variables["cos"] = std::make_shared<FunctionValue>(&cos);
        variables["sqrt"] = std::make_shared<FunctionValue>(&sqrt);
        variables["pow"] = std::make_shared<FunctionValue>(&pow);
        variables["max"] = std::make_shared<FunctionValue>(&max);
        variables["random"] = std::make_shared<FunctionValue>(&random);
        variables["mod"] = std::make_shared<FunctionValue>(&mod);
        variables["round"] = std::make_shared<FunctionValue>(&round);
        variables["floor"] = std::make_shared<FunctionValue>(&floor);
        variables["ceil"] = std::make_shared<FunctionValue>(&ceil);

        variables["pi"] = std::make_shared<NumberValue>(3.14159265358979323846f);
        variables["e"] = std::make_shared<NumberValue>(2.71828182845904523536f);
    }

    std::shared_ptr<Value> MathModule::sin(Evaluator&, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("Math.sin", args.size(), 1);
        validateArgumentType("Math.sin", 0, args[0], ValueType::NumberValue);
        const auto arg = valueCast<NumberValue>(args[0])->value;
        return std::make_shared<NumberValue>(sinf(arg));
    }

    std::shared_ptr<Value> MathModule::cos(Evaluator&, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("Math.cos", args.size(), 1);
        validateArgumentType("Math.cos", 0, args[0], ValueType::NumberValue);
        const auto arg = valueCast<NumberValue>(args[0])->value;
        return std::make_shared<NumberValue>(cosf(arg));
    }

    std::shared_ptr<Value> MathModule::sqrt(Evaluator&, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("Math.sqrt", args.size(), 1);
        validateArgumentType("Math.sqrt", 0, args[0], ValueType::NumberValue);
        const auto arg = valueCast<NumberValue>(args[0])->value;
        return std::make_shared<NumberValue>(sqrtf(arg));
    }

    std::shared_ptr<Value> MathModule::pow(Evaluator&, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("Math.pow", args.size(), 2);
        validateArgumentType("Math.pow", 0, args[0], ValueType::NumberValue);
        validateArgumentType("Math.pow", 1, args[1], ValueType::NumberValue);
        const auto base = valueCast<NumberValue>(args[0])->value;
        const auto index = valueCast<NumberValue>(args[1])->value;
        return std::make_shared<NumberValue>(powf(base, index));
    }

    std::shared_ptr<Value> MathModule::max(Evaluator&, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("Math.max", args.size(), 1);
        validateArgumentType("Math.max", 0, args[0], ValueType::ArrayValue);
        const auto values = valueCast<ArrayValue>(args[0]);
        if (values->size() == 0) {
            return std::make_shared<NullValue>();
        }

        auto first = values->at(0);
        if (first->type != ValueType::NumberValue)
            throw EvaluateError("Math.max array elements must be numbers");

        float max = valueCast<NumberValue>(first)->value;
        for (size_t i = 1; i < values->size(); ++i) {
            auto val = values->at(i);
            if (val->type != ValueType::NumberValue)
                throw EvaluateError("Math.max array elements must be numbers");
            float value = valueCast<NumberValue>(val)->value;
            if (value > max)
                max = value;
        }

        return std::make_shared<NumberValue>(max);
    }

    std::shared_ptr<Value> MathModule::random(Evaluator&, std::vector<std::shared_ptr<Value>>& args) {
        std::random_device dev;
        std::mt19937 rng(dev());

        if (args.size() == 0) {
            std::uniform_real_distribution<> dist(0.0, 1.0);
            return std::make_shared<NumberValue>((float) dist(rng));
        } else if (args.size() == 2) {
            validateArgumentType("Math.random", 0, args[0], ValueType::NumberValue);
            validateArgumentType("Math.random", 1, args[1], ValueType::NumberValue);

            float min = valueCast<NumberValue>(args[0])->value;
            float max = valueCast<NumberValue>(args[1])->value;
            std::uniform_real_distribution<> dist(min, max);
            return std::make_shared<NumberValue>((float) dist(rng));
        }

        throw EvaluateError("Math.random expects either 0 or 2 arguments");
    }

	std::shared_ptr<Value> MathModule::mod(Evaluator&, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("Math.mod", args.size(), 2);
        validateArgumentType("Math.mod", 0, args[0], ValueType::NumberValue);
        validateArgumentType("Math.mod", 1, args[1], ValueType::NumberValue);
		const auto left = valueCast<NumberValue>(args[0])->value;
		const auto right = valueCast<NumberValue>(args[1])->value;
		return std::make_shared<NumberValue>(std::fmod(left, right));
	}

    std::shared_ptr<Value> MathModule::round(Evaluator&, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("Math.round", args.size(), 1);
        validateArgumentType("Math.round", 0, args[0], ValueType::NumberValue);
        const auto num = valueCast<NumberValue>(args[0])->value;
        return std::make_shared<NumberValue>(std::floor(num + 0.5f));
    }

    std::shared_ptr<Value> MathModule::floor(Evaluator&, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("Math.floor", args.size(), 1);
        validateArgumentType("Math.floor", 0, args[0], ValueType::NumberValue);
        const auto num = valueCast<NumberValue>(args[0])->value;
        return std::make_shared<NumberValue>(std::floor(num));
    }

    std::shared_ptr<Value> MathModule::ceil(Evaluator&, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("Math.ceil", args.size(), 1);
        validateArgumentType("Math.ceil", 0, args[0], ValueType::NumberValue);
        const auto num = valueCast<NumberValue>(args[0])->value;
        return std::make_shared<NumberValue>(std::ceil(num));
    }
}
