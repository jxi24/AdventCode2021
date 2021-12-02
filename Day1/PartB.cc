#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main() {
    int current = 0, previous = -1;
    std::fstream data("input.txt");
    std::string line;
    int answer = 0;
    int count = 0;
    int token = 0;
    std::vector<int> save;
    while(std::getline(data, line)) {
        token = std::stoi(line);
        save.push_back(token);
        if(count < 3) {
            previous += token;
        } else {
            current = previous + token - save[count-3];
            if(current > previous) answer++;
        }
        count++;
    }

    std::cout << answer << std::endl;

    return 0;
}
