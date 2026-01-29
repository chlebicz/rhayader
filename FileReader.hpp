#pragma once
#include <fstream>
#include <string>
#include "tokenizer/Tokenizer.hpp"
#include "parser/Parser.hpp"

namespace rhayader {
	class Evaluator;
}

class FileReader {
public:
	FileReader(const std::string& fileName, rhayader::Evaluator& evaluator);
	void execute();
	bool ok();

private:
	rhayader::Tokenizer tokenizer;

	std::string line, previousLine;
	std::ifstream file;
	rhayader::Evaluator& evaluator;

	void readLine();
};