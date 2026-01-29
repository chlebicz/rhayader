#include "IO.hpp"
#include <iostream>
#include "Validation.hpp"

namespace rhayader {
    IOModule::IOModule(Evaluator& evaluator) : ModuleValue{evaluator, "IO"} {
        std::ios_base::sync_with_stdio(false);

        variables["print"] = std::make_shared<FunctionValue>(&print);
        variables["input"] = std::make_shared<FunctionValue>(&input);
    }

    std::shared_ptr<Value> IOModule::print(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        // print accepts any number of arguments of any type.
        for (const auto& arg : args)
            std::cout << arg->dump() << " ";
        std::cout << "\n";
        return std::make_shared<NullValue>();
    }

    std::shared_ptr<Value> IOModule::input(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("IO.input", args.size(), 0);
        std::string result;
        std::getline(std::cin, result);
        return std::make_shared<StringValue>(result);
    }
}
