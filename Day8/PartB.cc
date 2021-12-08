#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <map>
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

std::map<std::string, int> Decode(const std::string &input) {
    std::vector<std::string> scrambled;
    tokenize(input, scrambled);
    std::map<std::string, int> results;

    for(auto &digit : scrambled) {
        std::sort(digit.begin(), digit.end());
    }

    std::vector<std::string> digits(10);
    for(const auto &digit : scrambled) {
        if(digit.size() == 2) digits[1] = digit;
        else if(digit.size() == 3) digits[7] = digit;
        else if(digit.size() == 4) digits[4] = digit;
        else if(digit.size() == 7) digits[8] = digit;
    }

    for(const auto &digit : scrambled) {
        if(digit.size() == 6) {
            bool isNine = true;
            for(const auto &letter : digits[4]) {
                if(digit.find(letter) == std::string::npos) {
                    isNine = false;
                    break;
                }
            }
            if(isNine) digits[9] = digit;
            else {
                bool isZero = true;
                for(const auto &letter : digits[1]) {
                    if(digit.find(letter) == std::string::npos) {
                        isZero = false;
                        break;
                    }
                }
                if(isZero) digits[0] = digit;
                else digits[6] = digit;
            }
        }
    }

    char c;
    for(const auto &letter : digits[8]) {
        if(digits[6].find(letter) == std::string::npos)
            c = letter;
    }

    for(const auto &digit : scrambled) {
        if(digit.size() == 5) {
            bool isThree = true;
            for(const auto &letter : digits[7]) {
                if(digit.find(letter) == std::string::npos) {
                    isThree = false;
                    break;
                }
            }
            if(isThree) digits[3] = digit;
            else {
                if(digit.find(c) != std::string::npos)
                    digits[2] = digit;
                else digits[5] = digit;
            }
        }
    }

    for(size_t i = 0; i < digits.size(); ++i) {
        results[digits[i]] = i;
    }

    return results;
}

int main() {
    std::ifstream data("input.txt");
    std::string line;
    int count = 0;

    // Parse the data
    while(std::getline(data, line)) {
        auto pos = line.find_first_of("|");
        // Decode
        auto decoded = Decode(line.substr(0, pos));
        line = line.substr(pos+1, line.length());

        // Read results
        std::vector<std::string> tokens;
        tokenize(line, tokens);
        int reading = 0;
        for(size_t i = 0; i < tokens.size(); ++i) {
            std::sort(tokens[i].begin(), tokens[i].end());
            reading += std::pow(10, 3-i)*decoded[tokens[i]];
        }
        count += reading;
    }

    std::cout << "Reading results: " << count << std::endl;

    return 0;
}
