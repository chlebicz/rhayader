#include "String.hpp"
#include "../EvaluateError.hpp"
#include "Validation.hpp"
#include <algorithm>

namespace rhayader {
    StringModule::StringModule(Evaluator& evaluator) : ModuleValue{evaluator, "String"} {
        variables["split"] = std::make_shared<FunctionValue>(&split);
        variables["at"] = std::make_shared<FunctionValue>(&at);
        variables["slice"] = std::make_shared<FunctionValue>(&slice);
        variables["length"] = std::make_shared<FunctionValue>(&length);
        variables["starts_with"] = std::make_shared<FunctionValue>(&starts_with);
        variables["ends_with"] = std::make_shared<FunctionValue>(&ends_with);
        variables["contains"] = std::make_shared<FunctionValue>(&contains);
        variables["replace_all"] = std::make_shared<FunctionValue>(&replace_all);
        variables["from_int"] = std::make_shared<FunctionValue>(&from_int);
        variables["index_of"] = std::make_shared<FunctionValue>(&index_of);
        variables["to_upper"] = std::make_shared<FunctionValue>(&to_upper);
        variables["to_lower"] = std::make_shared<FunctionValue>(&to_lower);
        variables["characters"] = std::make_shared<FunctionValue>(&characters);
        variables["to_string"] = std::make_shared<FunctionValue>(&to_string);
        variables["reverse"] = std::make_shared<FunctionValue>(&reverse);
    }

    std::shared_ptr<Value> StringModule::split(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("String.split", args.size(), 2);
        validateArgumentType("String.split", 0, args[0], ValueType::StringValue);
        validateArgumentType("String.split", 1, args[1], ValueType::StringValue);

        const auto& str = valueCast<StringValue>(args[0])->value;
        const auto& delimiter = valueCast<StringValue>(args[1])->value;

        auto result = std::make_shared<ArrayValue>();
        size_t start = 0;
        auto end = str.find(delimiter);
        while (end != std::string::npos) {
            std::string element = str.substr(start, end - start);
            result->add(std::make_shared<StringValue>(element));
            start = end + delimiter.length();
            end = str.find(delimiter, start);
        }
        std::string element = str.substr(start, end);
        result->add(std::make_shared<StringValue>(element));

        return result;
    }

    std::shared_ptr<Value> StringModule::at(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("String.at", args.size(), 2);
        validateArgumentType("String.at", 0, args[0], ValueType::StringValue);
        validateArgumentType("String.at", 1, args[1], ValueType::NumberValue);

        const auto& str = valueCast<StringValue>(args[0])->value;
        auto indexVal = valueCast<NumberValue>(args[1])->value;
        if (indexVal < 0) return std::make_shared<NullValue>();

        const auto index = static_cast<size_t>(indexVal);
        if (index >= str.length()) return std::make_shared<NullValue>();

        const auto result = std::string(1, str[index]);
        return std::make_shared<StringValue>(result);
    }

    std::shared_ptr<Value> StringModule::slice(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("String.slice", args.size(), 2, 3);
        validateArgumentType("String.slice", 0, args[0], ValueType::StringValue);
        validateArgumentType("String.slice", 1, args[1], ValueType::NumberValue);
        if (args.size() >= 3)
             validateArgumentType("String.slice", 2, args[2], ValueType::NumberValue);

        const auto& str = valueCast<StringValue>(args[0])->value;
        auto startVal = valueCast<NumberValue>(args[1])->value;

        const auto start = static_cast<size_t>(startVal < 0 ? 0 : startVal);
        const auto end = args.size() >= 3 ? static_cast<size_t>(valueCast<NumberValue>(args[2])->value) : str.length();

        if (start >= str.length()) return std::make_shared<StringValue>("");

        try {
            return std::make_shared<StringValue>(str.substr(start, end));
        } catch (const std::out_of_range&) {
            // substr throws if start > size. We checked start >= length, but technically length could be slightly less than size? No.
            // But strict safety catch.
             return std::make_shared<StringValue>("");
        }
    }

    std::shared_ptr<Value> StringModule::length(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("String.length", args.size(), 1);
        validateArgumentType("String.length", 0, args[0], ValueType::StringValue);

        const auto str = valueCast<StringValue>(args[0]);
        return std::make_shared<NumberValue>((float) str->length());
    }

    std::shared_ptr<Value> StringModule::starts_with(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("String.starts_with", args.size(), 2);
        validateArgumentType("String.starts_with", 0, args[0], ValueType::StringValue);
        validateArgumentType("String.starts_with", 1, args[1], ValueType::StringValue);

        const auto& str = valueCast<StringValue>(args[0])->value;
        const auto& substr = valueCast<StringValue>(args[1])->value;

        if (substr.length() > str.length()) return std::make_shared<BooleanValue>(false);

        for (unsigned int i = 0; i < substr.length(); ++i) {
            if (str[i] != substr[i])
                return std::make_shared<BooleanValue>(false);
        }

        return std::make_shared<BooleanValue>(true);
    }

    std::shared_ptr<Value> StringModule::ends_with(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("String.ends_with", args.size(), 2);
        validateArgumentType("String.ends_with", 0, args[0], ValueType::StringValue);
        validateArgumentType("String.ends_with", 1, args[1], ValueType::StringValue);

        const auto& str = valueCast<StringValue>(args[0])->value;
        const auto& substr = valueCast<StringValue>(args[1])->value;

        if (substr.length() > str.length()) return std::make_shared<BooleanValue>(false);

        for (int i = (int) str.length() - 1, j = (int) substr.length() - 1; j >= 0; --i, --j) {
            if (str[i] != substr[j])
                return std::make_shared<BooleanValue>(false);
        }

        return std::make_shared<BooleanValue>(true);
    }

    std::shared_ptr<Value> StringModule::contains(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("String.contains", args.size(), 2);
        validateArgumentType("String.contains", 0, args[0], ValueType::StringValue);
        validateArgumentType("String.contains", 1, args[1], ValueType::StringValue);

        const auto& str = valueCast<StringValue>(args[0])->value;
        const auto& substr = valueCast<StringValue>(args[1])->value;
        return std::make_shared<BooleanValue>(str.find(substr) != std::string::npos);
    }

    std::shared_ptr<Value> StringModule::replace_all(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("String.replace_all", args.size(), 3);
        validateArgumentType("String.replace_all", 0, args[0], ValueType::StringValue);
        validateArgumentType("String.replace_all", 1, args[1], ValueType::StringValue);
        validateArgumentType("String.replace_all", 2, args[2], ValueType::StringValue);

        const auto str = valueCast<StringValue>(args[0]->clone());
        const auto& substr = valueCast<StringValue>(args[1])->value;
        const auto& replaceWith = valueCast<StringValue>(args[2])->value;

        str->replaceAll(substr, replaceWith);
        return str;
    }

    std::shared_ptr<Value> StringModule::from_int(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("String.from_int", args.size(), 1);
        validateArgumentType("String.from_int", 0, args[0], ValueType::NumberValue);

        const auto value = static_cast<int>(valueCast<NumberValue>(args[0])->value);
        return std::make_shared<StringValue>(std::to_string(value));
    }

    std::shared_ptr<Value> StringModule::index_of(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("String.index_of", args.size(), 2);
        validateArgumentType("String.index_of", 0, args[0], ValueType::StringValue);
        validateArgumentType("String.index_of", 1, args[1], ValueType::StringValue);

        const auto& str = valueCast<StringValue>(args[0])->value;
        const auto& substr = valueCast<StringValue>(args[1])->value;
        return std::make_shared<NumberValue>((float) str.find(substr));
    }

    std::shared_ptr<Value> StringModule::to_upper(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("String.to_upper", args.size(), 1);
        validateArgumentType("String.to_upper", 0, args[0], ValueType::StringValue);

        const auto str = valueCast<StringValue>(args[0]->clone());
        str->toUpperCase();
        return str;
    }

    std::shared_ptr<Value> StringModule::to_lower(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("String.to_lower", args.size(), 1);
        validateArgumentType("String.to_lower", 0, args[0], ValueType::StringValue);

        const auto str = valueCast<StringValue>(args[0]->clone());
        str->toLowerCase();
        return str;
    }

    std::shared_ptr<Value> StringModule::characters(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("String.characters", args.size(), 1);
        validateArgumentType("String.characters", 0, args[0], ValueType::StringValue);

        const auto str = valueCast<StringValue>(args[0]);

        auto result = std::make_shared<ArrayValue>();
        for (const char c : str->value) {
            result->add(std::make_shared<StringValue>(std::string(1, c)));
        }

        return result;
    }

    std::shared_ptr<Value> StringModule::to_string(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("String.to_string", args.size(), 1);
        // Any type is allowed
        return std::make_shared<StringValue>(args[0]->dump());
    }

    std::shared_ptr<Value> StringModule::reverse(Evaluator&, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("String.reverse", args.size(), 1);
        validateArgumentType("String.reverse", 0, args[0], ValueType::StringValue);

        const auto str = valueCast<StringValue>(args[0]->clone());
        std::reverse(str->value.begin(), str->value.end());
        return str;
    }
}
