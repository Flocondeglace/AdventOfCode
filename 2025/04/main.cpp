#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


// Function to read the rolls map from input
void ReadRollsMap(std::ifstream& input, std::vector<std::vector<int>>& rollsMap) {
    std::string line;
    while (std::getline(input, line)) {
        rollsMap.push_back(std::vector<int>());
        for (char c : line){
            int value = 0;
            if (c == '@'){
                value = 1;
            }
            rollsMap.back().push_back(value);
        }
    }
}



void CountRollsAccessible(std::ifstream& input, bool removeRolls = false) {
    std::string line;
    std::vector<std::vector<int>> rollsMap;
    std::vector<std::vector<int>> adjacentRollsNumberMap;
    std::vector<std::pair<int, int>> rollsToRemove;
    std::vector<std::pair<int, int>> rollsToRemoveNext;
    int totalAccessibleRolls = 0;

    ReadRollsMap(input, rollsMap);

    int numRows = rollsMap.size();
    int numCols = rollsMap[0].size();

    // Initialize adjacent rolls number map
    for (int i = 0; i < numRows; i++) {
        adjacentRollsNumberMap.push_back(std::vector<int>());
        for (int j = 0; j < numCols; j++){
            adjacentRollsNumberMap[i].push_back(0);
            if (rollsMap[i][j] == 1){ // if there is a roll, check if accessible
                // check 8 adjacent positions
                for (int k = std::max(0, i-1); k < std::min(i+2, numRows); k++){
                    for (int l = std::max(0, j-1); l < std::min(j+2, numCols); l++){
                        if (k!=i || l!=j) {
                            adjacentRollsNumberMap[i][j]+= rollsMap[k][l];
                        }
                    }
                }
                if (adjacentRollsNumberMap[i][j] < 4) { // accessible = less than 4 adjacent rolls
                    rollsToRemove.push_back(std::make_pair(i, j));
                }
            }
        }
    }
    totalAccessibleRolls = rollsToRemove.size();
    if (removeRolls) {
       
        // std::cout << "Initial Rolls to remove: " << rollsToRemove.size() << std::endl;
        while (rollsToRemove.size() > 0)
        {
            rollsToRemoveNext.clear();
            // Remove rolls
            for (std::pair<int, int> rollPos : rollsToRemove) {
                rollsMap[rollPos.first][rollPos.second] = 0;
            }
            for (std::pair<int, int> rollPos : rollsToRemove) {
                for (int k = std::max(0, rollPos.first-1); k < std::min(rollPos.first+2, numRows); k++){
                    for (int l = std::max(0, rollPos.second-1); l < std::min(rollPos.second+2, numCols); l++){
                        if (k!=rollPos.first || l!=rollPos.second) {
                            if (rollsMap[k][l] == 1){
                                adjacentRollsNumberMap[k][l] = adjacentRollsNumberMap[k][l]-1;
                                if (adjacentRollsNumberMap[k][l] == 3) { // roll to remove, ==3 to remove it just as soon as it become accessible
                                    rollsToRemoveNext.push_back(std::make_pair(k, l));
                                }
                            }
                        }
                    }
                }
                
            }
            rollsToRemove = rollsToRemoveNext;
            // std::cout << "Rolls to remove next: " << rollsToRemove.size() << std::endl;
            totalAccessibleRolls += rollsToRemove.size();
        }
    }
    std::cout << "Total Accessible Rolls: " << totalAccessibleRolls << std::endl;
}

int main() {
    std::cout << "Advent of Code 2025 - Day 04  " << std::endl;
    std::ifstream input;
    bool part1 ;

    for (int i = 1; i <= 2; i++) {
        std::cout << "---- Part " << i << " ----" << std::endl;
        part1 = (i == 1);


        std::cout << "-- Example --" << std::endl;
        input.open("input_example.txt");
        if (!input.is_open()) {
            std::cerr << "Failed to open input_example.txt" << std::endl;
            return 1;
        }
        CountRollsAccessible(input, !part1);
        input.close();

        std::cout << "-- Real Input --" << std::endl;
        input.open("input.txt");
        if (!input.is_open()) {
            std::cerr << "Failed to open input.txt" << std::endl;
            return 1;
        }
        CountRollsAccessible(input, !part1);
        input.close();
        std::cout << std::endl;
    }
}