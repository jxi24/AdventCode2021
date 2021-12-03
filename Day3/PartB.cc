#include <fstream>
#include <iostream>
#include <vector>
#include <string>

enum class Component {
    oxygen,
    co2
};

int IsSet(size_t num, int bit) {
    return ((num >> bit) & 1);
}

int CalcRating(Component comp, int bit, const std::vector<int> &readings) {
    // End recursion
    if(readings.size() == 1) return readings[0];

    std::vector<int> zero, one;
    for(const auto reading : readings) {
        if(IsSet(reading, bit)) one.push_back(reading);
        else zero.push_back(reading);
    }

    if(comp == Component::oxygen) {
        if(zero.size() > one.size()) {
            return CalcRating(comp, bit-1, zero);
        } else {
            return CalcRating(comp, bit-1, one);
        }
    } else {
        if(zero.size() > one.size()) {
            return CalcRating(comp, bit-1, one);
        } else {
            return CalcRating(comp, bit-1, zero);
        }
    }
}

int main() {
    std::fstream data("input.txt");
    std::string line;
    bool first = true;
    std::vector<int> readings;
    char *end;
    int nbits = 0;
    while(std::getline(data, line)) {
        if(first) {
            nbits = line.size();
            first = false;
        }
        readings.push_back(std::strtoul(line.c_str(), &end, 2));
    }

    int gen = CalcRating(Component::oxygen, nbits-1, readings);
    int scrub = CalcRating(Component::co2, nbits-1, readings);

    std::cout << "Oxygen Generator Rating: " << gen << "\n";
    std::cout << "CO2 Scrubber Rating: " << scrub << "\n";
    std::cout << "Result = " << gen * scrub << std::endl;
    
    return 0;
}
