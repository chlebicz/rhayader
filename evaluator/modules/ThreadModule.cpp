#include "ThreadModule.hpp"
#include "../Thread.hpp"
#include "../evaluator.hpp"
#include <sstream>
#include "Validation.hpp"

namespace rhayader {
	ThreadModule::ThreadModule(Evaluator& evaluator) : ModuleValue{evaluator, "Thread"} {
		variables["new"] = std::make_shared<FunctionValue>(&newthread);
		variables["sleep"] = std::make_shared<FunctionValue>(&sleep);
	}

	std::shared_ptr<Value> ThreadModule::newthread(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("Thread.new", args.size(), 1);
        validateArgumentType("Thread.new", 0, args[0], ValueType::FunctionValue);

		auto func = valueCast<FunctionValue>(args[0]);
		auto& thread = evaluator.thread.childThreads.emplace_back(func);

		std::stringstream s;
		s << thread.thread.get_id();

		return std::make_shared<StringValue>(s.str());
	}

	std::shared_ptr<Value> ThreadModule::sleep(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args) {
        validateArgumentCount("Thread.sleep", args.size(), 1);
        validateArgumentType("Thread.sleep", 0, args[0], ValueType::NumberValue);

		auto interval = valueCast<NumberValue>(args[0]);
		std::this_thread::sleep_for(std::chrono::milliseconds((int)interval->value));
		return std::make_shared<UndefinedValue>();
	}
}
