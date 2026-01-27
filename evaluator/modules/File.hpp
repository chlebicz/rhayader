#pragma once
#include "../values/values.hpp"

namespace rhayader {
	class FileModule : public ModuleValue {
	public:
		FileModule(Evaluator& evaluator);

	private:
		static std::shared_ptr<Value> read(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args);
		static std::shared_ptr<Value> write(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args);
		static std::shared_ptr<Value> append(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args);
		static std::shared_ptr<Value> exists(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args);
		static std::shared_ptr<Value> removeFile(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args);
		static std::shared_ptr<Value> mkdir(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args);
		static std::shared_ptr<Value> isDirectory(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args);
		static std::shared_ptr<Value> readDir(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args);
		static std::shared_ptr<Value> join(Evaluator& evaluator, std::vector<std::shared_ptr<Value>>& args);
	};
}
