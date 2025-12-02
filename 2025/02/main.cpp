#include <iostream>
#include <fstream>
#include <string>

bool countInvalidIdsPart1(std::string const id){
    if (id.size() % 2 == 0) {
        std::string x1 = id.substr(0, id.size() / 2);
        std::string x2 = id.substr(id.size()/2);
        return(x1 == x2);
    }
    return false;
}

bool countInvalidIdsPart2(std::string const id){
    if (id[0] == '0') {
        return false;
    }
    for (int i = 1; i <= id.size()/2; i++) {
        if (id.size() % i == 0) {
            std::string part = id.substr(0, i);
            int nbParts = 0;
            for (int j = 0; j*i < id.size(); j++) {
                if (id.substr(j*i, i) == part) {
                   nbParts++;
                }
            }
            if (nbParts == id.size()/i) return true;

        }
    }
    return false;
}


int main() {
    std::cout << "Advent of Code 2025 - Day 02" << std::endl;
    std::ifstream input;
    input.open("input.txt");

    if (!input.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    unsigned long start, end;
    unsigned long long sumPart1 = 0;
    unsigned long long sumPart2 = 0;
    while(std::getline(input, line, ',')) {
        start = std::stoul(line.substr(0, line.find('-')));
        end = std::stoul(line.substr(line.find('-') + 1));
        bool invalidPart1;
        bool invalidPart2;
        for (unsigned long i = start; i <= end; i++) {
            std::string numStr = std::to_string(i);
            if (countInvalidIdsPart1(numStr)) {
                sumPart1 += i;
            }
            if (countInvalidIdsPart2(numStr)) {
                std::cout << "Invalid Part 2: " << numStr << std::endl;
                sumPart2 += i;
            }
        }
    }
    std::cout << "Sum Part 1: " << sumPart1 << std::endl;
    std::cout << "Sum Part 2: " << sumPart2 << std::endl;
    input.close();
    return 0;
}