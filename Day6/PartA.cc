#include "Lanternfish.hh"
#include <iostream>
#include <fstream>
#include <vector>

template<class ContainerT>
void tokenize(const std::string& str, ContainerT& tokens,
              const std::string& delimiters=" \n\t", bool trimEmpty=true) {
    std::string::size_type lastPos = 0, length = str.length();
    
    using value_type = typename ContainerT::value_type;
    using size_type = typename ContainerT::size_type;

    while(lastPos < length+1) {
        std::string::size_type pos = str.find_first_of(delimiters, lastPos);
        if(pos == std::string::npos) pos = length;

        if(pos != lastPos || !trimEmpty) {
            tokens.push_back(value_type(str.data()+lastPos,
                             static_cast<size_type>(pos)-lastPos));
        }
        lastPos = pos+1;
    }
}

std::vector<int> ParseInput(const std::string& line) {
    std::vector<std::string> tokens;
    tokenize(line, tokens, ",");
    std::vector<int> results;
    for(const auto &token : tokens) {
        results.push_back(std::stoi(token));
    }
    return results;
}

int main() {
    // Get Input
    std::vector<LanternFish> fish;
    std::ifstream data("input.txt");
    std::string line;
    std::getline(data, line);
    std::vector<int> ages = ParseInput(line);

    for(const auto &age : ages) {
        fish.emplace_back(age);
    }

    // Simulate 80 days
    for(size_t i = 0; i < 80; ++i) {
        size_t nfish = fish.size();
        for(size_t j = 0; j < nfish; ++j) {
            if(fish[j].Age() == 0) fish.push_back(fish[j].Reset());
            else fish[j].Tick(); 
        }
    }

    std::cout << "There are " << fish.size() << " fish afer 80 days!" << std::endl;
    return 0;
}
