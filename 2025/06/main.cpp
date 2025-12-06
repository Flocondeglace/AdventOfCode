#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void ReadTextRightToLeftToVectors(std::string inputFile, std::vector<std::vector<unsigned long long>> &oData)
{
    std::ifstream input;
    input.open(inputFile);
    if (!input.is_open()) {
        std::cerr << "Failed to open " << inputFile << std::endl;
        return;
    }
    std::vector<std::vector<char>> dataChars;
    std::string line;
    bool firstLine = true;
    while (std::getline(input, line))
    {
        for (int i = 0; i < line.size(); i++) {
            if (firstLine) {
                dataChars.push_back(std::vector<char>());
            }
            dataChars[i].push_back(line[i]);
            
        }
        firstLine = false;
    }

    input.close();

    int op = 0;
    oData.push_back(std::vector<unsigned long long>());
    for (int i = 0; i < dataChars.size(); i++) {
        
        std::string column = "";
        for (int j = 0; j < dataChars[i].size(); j++) {
            if (dataChars[i][j] == '+') {
                op = 0;
            } else if (dataChars[i][j] == '*') {
                op = 1;
            }
            else if (dataChars[i][j] != ' ') {
                column += dataChars[i][j];
            }
        }
        if (!column.empty()) {
            oData.back().push_back(std::stoull(column));
        } else {
            oData.back().push_back(op);
            oData.push_back(std::vector<unsigned long long>());
        }
    }
    oData.back().push_back(op);
    
}

/**
 * Reads text file and populates vectors with data. At the end, put 1 for multiplication, 0 for addition.
 */
void ReadTextToVectors(std::string inputFile, std::vector<std::vector<unsigned long long>> &oData)
{
    std::ifstream input;
    input.open(inputFile);
    if (!input.is_open()) {
        std::cerr << "Failed to open " << inputFile << std::endl;
        return;
    }

    std::string line;
    bool firstLine = true;
    while (std::getline(input, line))
    {
        std::istringstream iss(line);
        std::string x;
        int columnIndex = 0;
        while (std::getline(iss, x, ' ')){
            if (x.empty()) {
                continue;
            }

            // operator conversion
            if (x == "+") {
                x = "0"; // addition
            } else if (x == "*") {
                x = "1"; // multiplication
            }

            if (firstLine) {
                oData.push_back(std::vector<unsigned long long>());
                oData.back().push_back(std::stoull(x));
            } else {
                oData[columnIndex].push_back(std::stoull(x));
            }
            columnIndex++;
        }
        firstLine = false;
    }
    input.close();
}

void Compute(std::vector<std::vector<unsigned long long>> const data)
{
    std::cout << "Computing results..." << std::endl;
    unsigned long long globalResult = 0;
    unsigned long long result = 0;
    for (int i = 0; i < data.size(); i++) {
        result = data[i][0];
        for (int j = 1; j < data[i].size() -1; j++) {
            if (data[i].back() == 1){ //multiplication
                result *= data[i][j];
            } else { // addition
                result += data[i][j];
            }
        }
        globalResult += result;
    }
    std::cout << "Global Result: " << globalResult << std::endl;
}

int main() {
    std::cout << "Advent of Code 2025 - Day 05  " << std::endl;
    std::cout << "-----------------------------" << std::endl;

    std::cout <<"---- Part 1" << std::endl;
    std::cout << "--- Example" << std::endl;
    std::vector<std::vector<unsigned long long>> data;
    ReadTextToVectors("input_example.txt", data);
    Compute(data);
    
    std::cout << "--- Real" << std::endl;
    data.clear();
    ReadTextToVectors("input.txt", data);
    Compute(data);

    std::cout <<"---- Part 2" << std::endl;
    std::cout << "--- Example" << std::endl;
    data.clear();
    ReadTextRightToLeftToVectors("input_example.txt", data);
    Compute(data);
    
    std::cout << "--- Real" << std::endl;
    data.clear();
    ReadTextRightToLeftToVectors("input.txt", data);
    Compute(data);
}