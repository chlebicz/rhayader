#include "File.hpp"
#include <filesystem>
#include <fstream>
#include "Validation.hpp"
#include "../values/StringValue.hpp"
#include "../values/BooleanValue.hpp"
#include "../values/MapValue.hpp"
#include "../values/ArrayValue.hpp"
#include "../values/NullValue.hpp"
#include "../valueCast.hpp"

namespace rhayader {
    FileModule::FileModule(Evaluator& evaluator) : ModuleValue{evaluator, "File"} {
        variables["read"] = std::make_shared<FunctionValue>(&read);
        variables["write"] = std::make_shared<FunctionValue>(&write);
        variables["append"] = std::make_shared<FunctionValue>(&append);
        variables["exists"] = std::make_shared<FunctionValue>(&exists);
        variables["delete"] = std::make_shared<FunctionValue>(&removeFile);
        variables["mkdir"] = std::make_shared<FunctionValue>(&mkdir);
        variables["is_directory"] = std::make_shared<FunctionValue>(&isDirectory);
        variables["read_dir"] = std::make_shared<FunctionValue>(&readDir);
        variables["join"] = std::make_shared<FunctionValue>(&join);
    }

    // Helper to get string arg
    static std::string getString(const std::shared_ptr<Value>& arg) {
        return valueCast<StringValue>(arg)->value;
    }

    std::shared_ptr<Value> FileModule::read(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("File.read", args.size(), 1);
        validateArgumentType("File.read", 0, args[0], ValueType::StringValue);

        std::string path = getString(args[0]);
        auto map = std::make_shared<MapValue>();

        if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path)) {
            map->set("ok", std::make_shared<BooleanValue>(false));
            return map;
        }

        std::ifstream file(path);
        if (!file.is_open()) {
             map->set("ok", std::make_shared<BooleanValue>(false));
             return map;
        }

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        map->set("ok", std::make_shared<BooleanValue>(true));
        map->set("content", std::make_shared<StringValue>(content));

        return map;
    }

    std::shared_ptr<Value> FileModule::write(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("File.write", args.size(), 2);
        validateArgumentType("File.write", 0, args[0], ValueType::StringValue);
        validateArgumentType("File.write", 1, args[1], ValueType::StringValue);

        std::string path = getString(args[0]);
        std::string content = getString(args[1]);

        std::ofstream file(path);
        if (!file.is_open()) return std::make_shared<BooleanValue>(false);

        file << content;
        return std::make_shared<BooleanValue>(true);
    }

    std::shared_ptr<Value> FileModule::append(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("File.append", args.size(), 2);
        validateArgumentType("File.append", 0, args[0], ValueType::StringValue);
        validateArgumentType("File.append", 1, args[1], ValueType::StringValue);

        std::string path = getString(args[0]);
        std::string content = getString(args[1]);

        std::ofstream file(path, std::ios_base::app);
        if (!file.is_open()) return std::make_shared<BooleanValue>(false);

        file << content;
        return std::make_shared<BooleanValue>(true);
    }

    std::shared_ptr<Value> FileModule::exists(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("File.exists", args.size(), 1);
        validateArgumentType("File.exists", 0, args[0], ValueType::StringValue);

        std::string path = getString(args[0]);
        return std::make_shared<BooleanValue>(std::filesystem::exists(path));
    }

    std::shared_ptr<Value> FileModule::removeFile(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("File.delete", args.size(), 1);
        validateArgumentType("File.delete", 0, args[0], ValueType::StringValue);

        std::string path = getString(args[0]);
        try {
            return std::make_shared<BooleanValue>(std::filesystem::remove(path));
        } catch (...) {
            return std::make_shared<BooleanValue>(false);
        }
    }

    std::shared_ptr<Value> FileModule::mkdir(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("File.mkdir", args.size(), 1);
        validateArgumentType("File.mkdir", 0, args[0], ValueType::StringValue);

        std::string path = getString(args[0]);
        try {
            return std::make_shared<BooleanValue>(std::filesystem::create_directory(path));
        } catch (...) {
             return std::make_shared<BooleanValue>(false);
        }
    }

    std::shared_ptr<Value> FileModule::isDirectory(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("File.is_directory", args.size(), 1);
        validateArgumentType("File.is_directory", 0, args[0], ValueType::StringValue);

        std::string path = getString(args[0]);
        try {
            return std::make_shared<BooleanValue>(std::filesystem::is_directory(path));
        } catch (...) {
            return std::make_shared<BooleanValue>(false);
        }
    }

    std::shared_ptr<Value> FileModule::readDir(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("File.read_dir", args.size(), 1);
        validateArgumentType("File.read_dir", 0, args[0], ValueType::StringValue);

        std::string path = getString(args[0]);
        auto map = std::make_shared<MapValue>();

        if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
             map->set("ok", std::make_shared<BooleanValue>(false));
             return map;
        }

        auto array = std::make_shared<ArrayValue>();
        try {
            for (const auto& entry : std::filesystem::directory_iterator(path)) {
                array->add(std::make_shared<StringValue>(entry.path().filename().string()));
            }
            map->set("ok", std::make_shared<BooleanValue>(true));
            map->set("files", array);
        } catch (...) {
            map->set("ok", std::make_shared<BooleanValue>(false));
        }

        return map;
    }

    std::shared_ptr<Value> FileModule::join(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        std::filesystem::path p;
        for (size_t i = 0; i < args.size(); ++i) {
            validateArgumentType("File.join", i, args[i], ValueType::StringValue);
            if (i == 0)
                p = getString(args[i]);
            else
                p /= getString(args[i]);
        }

        return std::make_shared<StringValue>(p.string());
    }
}
