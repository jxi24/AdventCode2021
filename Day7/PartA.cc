#include "Brent.hh"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
    // Setup
    std::ifstream data("input.txt");
    std::string line;
    std::vector<std::string> tokens;
    std::vector<int> positions;

    // Parse input
    std::getline(data, line);
    tokenize(line, tokens, ",");
    for(const auto &token : tokens) positions.push_back(std::stoi(token));

    // Minimize
    auto func = [&](double x) {
        double result = 0;
        for(const auto &position : positions) {
            result += std::abs(position - x);
        }
        return result;
    };
    Brent brent(func, 1e-3);
    auto result = int(brent.Minimize(0, *std::max_element(positions.begin(), positions.end())));
    std::cout << "Best horizontal position is at:\n";
    if(func(result) > func(result-1)) result--;
    std::cout << "  " << result << " with a fuel cost of " << func(result) << std::endl;

    return 0;
}
