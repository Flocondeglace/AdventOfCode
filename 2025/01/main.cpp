#include <fstream>
#include <iostream>
#include <string.h>

void part1() {
    std::ifstream input;
    input.open("input.txt");

    if (!input.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return;
    }
    std::string line;
    int currentPointingDirection = 50;
    int numberOfZeros = 0;
    while (std::getline(input, line)) {
        char direction = line[0];
        int value = std::stoi(line.substr(1));
        if (direction == 'L') {
            currentPointingDirection -= value;
        } else if (direction == 'R') {
            currentPointingDirection += value;
        }
        currentPointingDirection = currentPointingDirection % 100;
        if (currentPointingDirection == 0){
            numberOfZeros++;
        }
    }
    std::cout << "Number of zeros : " << numberOfZeros << std::endl;
    input.close();
}

void part2() {
    std::ifstream input;
    input.open("input.txt");

    if (!input.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return;
    }
    std::string line;
    int currentPointingDirection = 50;
    int numberOfZeros = 0;
    while (std::getline(input, line)) {
        char direction = line[0];
        int value = std::stoi(line.substr(1));
        if (direction == 'L') {
            currentPointingDirection -= value;
        } else if (direction == 'R') {
            currentPointingDirection += value;
        }
        numberOfZeros += (currentPointingDirection / 100);
        currentPointingDirection = currentPointingDirection % 100;
    }
    std::cout << "Number of zeros : " << numberOfZeros << std::endl;
    input.close();
}

int main() {
    std::cout << "Advent of Code 2025 - Day 01" << std::endl;

    std::cout << "Part 1:" << std::endl;
    part1();
    std::cout << "Part 2:" << std::endl;
    part2();
    
    return 0;
}