#include "GlobalScope.hpp"
#include "modules/Array.hpp"
#include "modules/IO.hpp"
#include "modules/Map.hpp"
#include "modules/String.hpp"
#include "modules/Math.hpp"
#include "modules/ThreadModule.hpp"
#include "modules/File.hpp"

namespace rhayader {
	GlobalScope::GlobalScope(Evaluator& evaluator) {
		variables["Array"] = std::make_shared<ArrayModule>(evaluator);
		variables["Map"] = std::make_shared<MapModule>(evaluator);
		variables["IO"] = std::make_shared<IOModule>(evaluator);
		variables["String"] = std::make_shared<StringModule>(evaluator);
		variables["Math"] = std::make_shared<MathModule>(evaluator);
		variables["Thread"] = std::make_shared<ThreadModule>(evaluator);
		variables["File"] = std::make_shared<FileModule>(evaluator);
	}
}
