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

int main() {
    std::ifstream data("input.txt");
    std::string line;
    int count = 0;

    // Parse the data
    while(std::getline(data, line)) {
        std::vector<std::string> tokens;
        auto pos = line.find_first_of("|");
        line = line.substr(pos+1, line.length());
        tokenize(line, tokens);
        for(const auto &token : tokens) {
            if(token.size() == 2 || token.size() == 3 || token.size() == 4 || token.size() == 7)
                count++;
        }
    }

    std::cout << "Number of 1,4,7,8: " << count << std::endl;

    return 0;
}
