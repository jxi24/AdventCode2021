#include "Hydrothermal.hh"
#include <string>
#include <fstream>

Point ParsePoint(const std::string &line) {
    Point point;
    std::size_t delim = line.find_first_of(",");
    point.x = std::stoi(line.substr(0, delim));
    point.y = std::stoi(line.substr(delim+1));
    return point;
}

std::pair<Point, Point> ParseLine(const std::string &line) {
    std::pair<Point, Point> result;

    std::size_t delim = line.find_first_of(" -> ");
    std::string start = line.substr(0, delim);
    std::string end = line.substr(delim + 4);
    
    result.first = ParsePoint(start);
    result.second = ParsePoint(end);

    return result;
}

int main() {
    SeaFloor floor(1000, 1000);
    std::ifstream data("input.txt");
    std::string line;

    while(std::getline(data, line)) {
        auto vents = ParseLine(line);
        floor.AddVent(vents.first, vents.second, false);
    }

    floor.PrintMap();
    std::cout << "Dangerous locations = " << floor.CalcDanger() << std::endl;

    return 0;
}
