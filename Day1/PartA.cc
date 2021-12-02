#include <fstream>
#include <string>
#include <iostream>

int main() {
    int current = 0, previous = -1;
    std::fstream data("input.txt");
    std::string line;
    int answer = 0;
    while(std::getline(data, line)) {
        current = std::stoi(line);
        if(previous != -1 && current > previous) answer++;
        previous = current;
    }

    std::cout << answer << std::endl;

    return 0;
}
