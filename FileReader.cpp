#include "FileReader.hpp"
#include "evaluator/evaluator.hpp"

FileReader::FileReader(const std::string& fileName, rhayader::Evaluator& evaluator)
	: evaluator(evaluator), file{fileName}
{}

void FileReader::execute() {
	while (std::getline(file, line)) {
		readLine();
	}
}

bool FileReader::ok() {
	return file.is_open();
}

void FileReader::readLine() {
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
			if (file.peek() == EOF) {
				std::cout << "ParseError: parser needs a token, but file finished reading" << std::endl;
				exit(69);
			}

			previousLine = line;
		} else {
			error.print();
		}
		return;
	}

	previousLine = "";

	try {
		evaluator.evaluate(tree);
	} catch (const rhayader::Error& error) {
		error.print();
	}
}
