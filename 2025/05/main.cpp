#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void ReadRangesAndIngredients(std::string inputFile, std::vector<unsigned long long> &oIngredients, std::vector<std::pair<unsigned long long, unsigned long long>> &oRanges)
{
    std::ifstream input;
    input.open(inputFile);
    if (!input.is_open()) {
        std::cerr << "Failed to open " << inputFile << std::endl;
        return;
    }

    std::string line;
    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        unsigned long long dashPos = line.find('-');
        if (dashPos == std::string::npos) {
            oIngredients.push_back(std::stoull(line));
        } else {
            unsigned long long rangeStart = std::stoull(line.substr(0, dashPos));
            unsigned long long rangeEnd = std::stoull(line.substr(dashPos + 1));
            oRanges.push_back(std::make_pair(rangeStart, rangeEnd));
        }
    }
    std::cout << "Read " << oRanges.size() << " ranges and " << oIngredients.size() << " ingredients from " << inputFile << std::endl;
    
    input.close();
}

void CountFreshIngredientsInList(std::vector<unsigned long long> const ingredients, std::vector<std::pair<unsigned long long, unsigned long long>> ranges)
{
    int freshCount = 0;
    for (unsigned long long ingredient : ingredients) {
        bool isFresh = false;
        for (std::pair<unsigned long long, unsigned long long> &range : ranges) {
            if (ingredient >= range.first && ingredient <= range.second) {
                isFresh = true;
                break;
            }
        }
        if (isFresh) {
            freshCount++;
        }
    }
    std::cout << "Number of fresh ingredients: " << freshCount << std::endl;
}

void CountIdsConsideredFresh(std::vector<std::pair<unsigned long long, unsigned long long>> ranges)
{
    unsigned long long freshCount = 0;
    std::vector<std::pair<unsigned long long, unsigned long long>> mergedRanges;
    while (!ranges.empty())
    {
        std::pair<unsigned long long, unsigned long long> currentRange = ranges.back();
        std::vector<std::pair<unsigned long long, unsigned long long>> newRanges;
        unsigned long long first = currentRange.first;
        unsigned long long last = currentRange.second;
        // std::cout << "Merged ranges so far: " << mergedRanges.size() << std::endl;
        for (std::pair<unsigned long long, unsigned long long> &range : mergedRanges)
        {
            if (range.first <= first && range.second >= first)
            {
                first = range.second + 1;
            }

            if (last <= range.second && last >= range.first)
            {
                last = range.first - 1;
            }

            if (first <= range.first && last >= range.second)
            {
                newRanges.push_back(std::make_pair(first, range.first - 1));
                newRanges.push_back(std::make_pair(range.second + 1, last));
                // std::cout << "  Splitting range [" << currentRange.first << ", " << currentRange.second << "] into [" << first << ", " << (range.first - 1) << "] and [" << newRanges.back().first << ", " << newRanges.back().second << "] due to overlap with [" << range.first << ", " << range.second << "]" << std::endl;
                first = last + 1; // Mark as fully processed
                break;
            }
        }
        // std::cout << "Processing range [" << currentRange.first << ", " << currentRange.second << "] -> fresh subrange [" << first << ", " << last << "]" << std::endl;
        if (last >= first)
        {
            freshCount += (last - first + 1);
            // std::cout << "FreshCount updated to " << freshCount << std::endl;
            mergedRanges.push_back(std::make_pair(first, last));
        }
        ranges.pop_back();
        ranges.insert(ranges.end(), newRanges.begin(), newRanges.end());
    }
    std::cout << "Number of fresh IDs: " << freshCount << std::endl;
}

int main() {
    std::cout << "Advent of Code 2025 - Day 05  " << std::endl;
    std::cout << "-----------------------------" << std::endl;
    
    std::vector<std::pair<unsigned long long, unsigned long long>> ranges;
    std::vector<unsigned long long> ingredients;
    std::cout << "--- Example" << std::endl;
    ReadRangesAndIngredients("input_example.txt", ingredients, ranges);
    CountFreshIngredientsInList(ingredients, ranges);
    CountIdsConsideredFresh(ranges);

    ingredients.clear();
    ranges.clear();
    std::cout << std::endl << "--- Real" << std::endl;
    ReadRangesAndIngredients("input.txt", ingredients, ranges);
    CountFreshIngredientsInList(ingredients, ranges);
    CountIdsConsideredFresh(ranges);
}