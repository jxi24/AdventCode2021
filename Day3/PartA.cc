#include <fstream>
#include <iostream>
#include <vector>
#include <string>

int IsSet(size_t num, int bit) {
    return ((num >> bit) & 1);
}

void ParseLine(const std::string &line, std::vector<int> &bits) {
    char *end;
    auto val = std::strtoul(line.c_str(), &end, 2);
    for(size_t i = bits.size(); i > 0; --i) {
        bits[bits.size()-i] += 2*IsSet(val, i-1)-1;
    }
}

int main() {
    std::fstream data("input.txt");
    std::string line;
    bool first = true;
    std::vector<int> bits;
    while(std::getline(data, line)) {
        if(first) bits.resize(line.size());
        ParseLine(line, bits);
    }
    
    std::string gamma_str, epsilon_str;
    for(size_t i = 0; i < bits.size(); ++i) {
        if(bits[i] < 0) {
            gamma_str += "0";
            epsilon_str += "1";
        } else {
            gamma_str += "1";
            epsilon_str += "0";
        }
    }

    char* end;
    auto gamma = std::strtoul(gamma_str.c_str(), &end, 2);
    auto epsilon = std::strtoul(epsilon_str.c_str(), &end, 2);

    std::cout << "Gamma = " << gamma << " Epsilon = " << epsilon << "\n";
    std::cout << "Result = " << gamma * epsilon << std::endl;
    return 0;
}
