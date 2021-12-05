#include "Board.hh"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

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
    std::vector<int> numbers;
    std::vector<Board> boards;
    std::string line;

    std::getline(data, line);

    std::stringstream linestream(line);
    while(std::getline(linestream, line, ',')) {
        numbers.push_back(std::stoi(line));
    }

    // The first line is blank, followed by 5 for the board
    while(std::getline(data, line)) {
        std::array<int, 25> board;
        for(size_t i = 0; i < 5; ++i) {
            std::getline(data, line);
            std::vector<std::string> tokens;
            tokenize(line, tokens);
            for(size_t j = 0; j < 5; ++j) {
                board[5*i + j] = std::stoi(tokens[j]);
            }
        }

        boards.push_back(Board(board));
    }

    // Mark boards
    std::vector<bool> winners(boards.size(), false);
    int nwinners = 0;
    int count = 0;
    while(nwinners != boards.size()) {
        size_t idx = 0;
        for(auto & board : boards) {
            board.Mark(numbers[count]);
            if(board.Winner()) {
                if(!winners[idx]) {
                    winners[idx] = true;
                    nwinners++;
                    if(nwinners == boards.size()) {
                        std::cout << "Last to win has score = " << board.Score(numbers[count]) << std::endl;
                        break;
                    }
                }
            }
            idx++;
        }
        count++;
    }

    return 0;
}
