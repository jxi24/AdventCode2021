#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum class Direction {
    forward,
    up,
    down
};

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

std::pair<Direction, int> ParseLine(const std::string &line) {
    std::vector<std::string> tokens;
    tokenize(line, tokens);
    std::pair<Direction, int> result;
    if(tokens[0] == "forward") result.first = Direction::forward;
    else if(tokens[0] == "up") result.first = Direction::up;
    else if(tokens[0] == "down") result.first = Direction::down;
    
    result.second = std::stoi(tokens[1]);

    return result;
}

int main() {
    std::ifstream data("input.txt");
    std::string line;
    int forward = 0;
    int depth = 0;

    while(std::getline(data, line)) {
        auto move = ParseLine(line);
        switch(move.first) {
            case Direction::forward:
                forward += move.second;
                break;
            case Direction::up:
                depth -= move.second;
                break;
            case Direction::down:
                depth += move.second;
                break;
        }
    }

    std::cout << "Forward: " << forward << " Depth: " << depth << "\n";
    std::cout << "Result: " << forward*depth << std::endl;
    return 0;
}
