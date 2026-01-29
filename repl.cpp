#include "repl.hpp"
#include <replxx.hxx>

static rhayader::Thread mainThread;
static replxx::Replxx rx;

std::string previousLine;
rhayader::Tokenizer tokenizer;

void getline() {
	std::string prompt = previousLine.empty() ? ">>> " : "... ";
	const char* input = rx.input(prompt);

	if (input == nullptr) {
		exit(0);
	}

	std::string line = input;
	if (!line.empty()) {
		rx.history_add(line);
	}

	line = previousLine + line;

	try {
		tokenizer.tokenize(line);
	} catch (const rhayader::Error& error) {
		error.print();
		return;
	}

	rhayader::Parser parser{tokenizer.getTokens()};

	std::shared_ptr<rhayader::Node> tree;
	try {
		tree = parser.parse();
	} catch (const rhayader::Error& error) {
		if (error.type == rhayader::ErrorType::NoTokens) {
			previousLine = line;
		} else {
			error.print();
		}
		return;
	}

	previousLine = "";

	try {
		const auto value = mainThread.evaluator->evaluate(tree);
		std::cout << value->dump() << std::endl;
	} catch (const rhayader::Error& error) {
		error.print();
	}
}
