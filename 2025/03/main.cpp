#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

bool CompareBatteries(std::pair<int, int> const& a, std::pair<int, int> const& b) {
    return (a.second > b.second || (a.second == b.second && a.first < b.first));
}

void ComputeBankVoltage(std::vector<std::pair<int, int>> const& batteriesJoltage, int numBatteriesToFindValue, std::string &oBankVoltage){
    int numBatteriesToFind = numBatteriesToFindValue;
    int idxLastBatteryAdded = -1;
    // Take the max and iterate to find a following battery
    oBankVoltage = "";
    while (numBatteriesToFind > 0){
        for (std::pair<int, int> battery : batteriesJoltage) {
            if (((battery.first > idxLastBatteryAdded) && battery.first < batteriesJoltage.size() - numBatteriesToFind) || (battery.first == batteriesJoltage.size() - numBatteriesToFind)) {
                oBankVoltage += std::to_string(battery.second);
                idxLastBatteryAdded = battery.first;
                numBatteriesToFind--;
                break;
            }
        }
    }
}

void ComputeVoltage(std::ifstream& input, int part) {
    std::string line;
    std::vector<std::pair<int, int>> batteriesJoltage;
    long long unsigned int globalJoltage = 0;
    while(std::getline(input, line)) {
        batteriesJoltage.clear();
        for (int i = 0; i < line.size(); i++) {
            batteriesJoltage.push_back(std::make_pair(i, std::stoi(std::string(1, line[i]))));
        }
        std::sort(batteriesJoltage.begin(), batteriesJoltage.end(), CompareBatteries);
        
        std::string bankVoltage = "";
        if (part == 1) {
            ComputeBankVoltage(batteriesJoltage, 2, bankVoltage);

        } else {
            ComputeBankVoltage(batteriesJoltage, 12, bankVoltage);
        }
        globalJoltage += std::stoll(bankVoltage);
    }
    std::cout << "Global Joltage : " << globalJoltage << std::endl;

}

int main() {
    std::cout << "Advent of Code 2025 - Day 03" << std::endl;
    std::ifstream input;

    for (int i = 1; i <= 2; i++) {
        std::cout << "---- Part " << i << " ----" << std::endl;
    
        input.open("input_example.txt");
        if (!input.is_open()) {
            std::cerr << "Failed to open input_example.txt" << std::endl;
            return 1;
        }
        ComputeVoltage(input,i);
        input.close();
        
        input.open("input.txt");
        if (!input.is_open()) {
            std::cerr << "Failed to open input.txt" << std::endl;
            return 1;
        }
        ComputeVoltage(input,i);
        input.close();
    }
}