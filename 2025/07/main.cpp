#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void CountTachyonBeams(const std::string& inputFile) {
    std::ifstream input;
    input.open(inputFile);
    if (!input.is_open()) {
        std::cerr << "Failed to open " << inputFile << std::endl;
        return;
    }

    std::string line;
    // Part 1
    unsigned splitCount = 0;
    std::vector<bool> tachyonBeamsColumns;
    std::vector<bool> tachyonBeamsColumnsNextLine;

    // Part 2
    std::vector<unsigned long> pathCounts;
    std::vector<unsigned long> pathCountsNextLine;

    // Start
    std::getline(input, line);
    tachyonBeamsColumnsNextLine.resize(line.size(), false);
    tachyonBeamsColumns.resize(line.size(), false);
    pathCounts.resize(line.size(), 0);
    pathCountsNextLine.resize(line.size(), 0);
    for (unsigned i = 0; i < line.size(); i++) {
        if (line[i] == 'S') { 
            tachyonBeamsColumns[i] = true;
            tachyonBeamsColumnsNextLine[i] = true;
            pathCounts[i] = 1;
            pathCountsNextLine[i] = 1;
        }
    }

    // Process lines
    while (std::getline(input, line)) {

        for (unsigned i = 0; i < line.size(); i++) {
            if (line[i] == '^') {
                // Part 1
                splitCount += tachyonBeamsColumns[i];
                tachyonBeamsColumnsNextLine[i-1] = tachyonBeamsColumns[i-1]||tachyonBeamsColumns[i];
                tachyonBeamsColumnsNextLine[i+1] = tachyonBeamsColumns[i+1]||tachyonBeamsColumns[i];
                tachyonBeamsColumnsNextLine[i] = false;
                
                // Part 2
                pathCountsNextLine[i-1] += pathCounts[i];
                pathCountsNextLine[i+1] += pathCounts[i];
                pathCountsNextLine[i] = 0;
            }
        }

        tachyonBeamsColumns = tachyonBeamsColumnsNextLine; // Part 1
        pathCounts = pathCountsNextLine; // Part 2
    }

    input.close();
    std::cout << "Total Tachyon Beams split: " << splitCount << std::endl;
    std::cout << "Total Paths to the End: ";
    unsigned long long totalPaths = 0;
    for (unsigned long count : pathCounts) {
        totalPaths += count;
    }
    std::cout << totalPaths << std::endl;
}

int main() {
    std::cout << "Advent of Code 2025 - Day 05  " << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "--- Example" << std::endl;
    CountTachyonBeams("input_example.txt");
    std::cout << "--- Real Input" << std::endl;
    CountTachyonBeams("input.txt");
}