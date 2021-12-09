#include "HeightMap.hh"
#include <iostream>
#include <fstream>
#include <numeric>
#include <algorithm>

std::vector<int> ParseLine(const std::string &line) {
    std::vector<int> vals;
    for(const char num : line)
        vals.push_back(std::atoi(&num));
    return vals;
}

int main() {
    std::ifstream data("input.txt");
    std::string line;
    std::vector<std::vector<int>> rows;

    // Read Data
    while(std::getline(data, line)) {
        rows.push_back(ParseLine(line));
    }

    // Store in height map
    HeightMap map(rows.size(), rows[0].size());
    for(std::size_t i = 0; i < rows.size(); ++i)
        map.AddRow(i, rows[i]);
    auto points = map.FindLowPoints();
    auto basins = map.FindBasins();
    std::sort(basins.begin(), basins.end(), std::greater<int>());

    std::cout << "Basin sizes = " << basins[0]*basins[1]*basins[2] << std::endl;

    return 0;
}
