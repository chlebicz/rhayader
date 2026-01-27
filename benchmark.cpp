#include <iostream>
#include <chrono>
#include <vector>
#include <memory>
#include "evaluator/evaluator.hpp"
#include "evaluator/Thread.hpp"
#include "parser/nodes.hpp"
#include "evaluator/values/NumberValue.hpp"

using namespace rhayader;

int main() {
    Thread thread;

    // Create an assignment: x = 42
    auto xName = std::make_shared<NameNode>("x");
    auto value = std::make_shared<NumberNode>(42.0f);
    auto assignment = std::make_shared<EqualsOpNode>(xName, value);

    thread.evaluator->evaluate(assignment);

    // Now benchmark resolving "x"
    std::cout << "Benchmarking variable lookup..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    int iterations = 10000000;
    for (int i = 0; i < iterations; ++i) {
        thread.evaluator->evaluate(xName);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "Time taken for " << iterations << " lookups: " << diff.count() << " s" << std::endl;
    std::cout << "Time per lookup: " << (diff.count() / iterations) * 1e9 << " ns" << std::endl;

    return 0;
}
